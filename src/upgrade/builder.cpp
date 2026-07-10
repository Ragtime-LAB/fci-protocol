#include "florid_usb_protocol/upgrade/builder.hpp"

#include <cstring>

namespace florid::usb::upgrade {

namespace {

bool is_supported_image_id(std::uint8_t image_id)
{
    return image_id == to_u8(ImageId::Application);
}

bool is_supported_target_slot(std::uint8_t target_slot)
{
    return target_slot == to_u8(SlotId::Secondary);
}

} // namespace

tl::expected<UpgradePlan, UpgradePlanError> UpgradePlan::create(
    const FirmwareImage& image,
    std::uint16_t write_align,
    std::uint16_t max_chunk_size,
    std::uint8_t image_id,
    std::uint8_t target_slot)
{
    if (!is_supported_image_id(image_id))
    {
        return tl::make_unexpected(UpgradePlanError::InvalidImageId);
    }
    if (!is_supported_target_slot(target_slot))
    {
        return tl::make_unexpected(UpgradePlanError::InvalidTargetSlot);
    }

    auto chunk_plan = ChunkPlan::create(image, write_align, max_chunk_size);
    if (!chunk_plan)
    {
        return tl::make_unexpected(UpgradePlanError::ChunkPlanError);
    }

    return UpgradePlan(*chunk_plan, image_id, target_slot);
}

StartUpgradeRequest UpgradePlan::make_start_request(std::uint8_t req_id,
                                                    std::uint8_t flags) const
{
    StartUpgradeRequest request{};
    request.req_id = req_id;
    request.image_id = image_id_;
    request.target_slot = target_slot_;
    request.flags = flags;
    request.version = {};
    request.image_size = chunk_plan_.image_size();
    request.image_crc32 = chunk_plan_.image_crc32();
    return request;
}

FinishUpgradeRequest UpgradePlan::make_finish_request(std::uint8_t req_id,
                                                      std::uint32_t session_id) const
{
    FinishUpgradeRequest request{};
    request.req_id = req_id;
    request.image_id = image_id_;
    request.target_slot = target_slot_;
    request.reserved0 = 0;
    request.session_id = session_id;
    request.image_size = chunk_plan_.image_size();
    request.image_crc32 = chunk_plan_.image_crc32();
    return request;
}

SetPendingRequest UpgradePlan::make_set_pending_request(std::uint8_t req_id,
                                                        std::uint8_t flags) const
{
    SetPendingRequest request{};
    request.req_id = req_id;
    request.image_id = image_id_;
    request.target_slot = target_slot_;
    request.flags = flags;
    return request;
}

RebootRequest UpgradePlan::make_reboot_request(std::uint8_t req_id,
                                               std::uint8_t mode) const
{
    RebootRequest request{};
    request.req_id = req_id;
    request.mode = mode;
    request.reserved0 = 0;
    request.reserved1 = 0;
    return request;
}

tl::expected<ChunkRequest, UpgradePlanError> UpgradePlan::make_chunk_request(
    std::size_t index,
    std::uint8_t req_id,
    std::uint32_t session_id) const
{
    if (session_id == 0)
    {
        return tl::make_unexpected(UpgradePlanError::InvalidSessionId);
    }

    auto chunk = chunk_plan_.chunk_at(index, std::span<std::uint8_t>(scratch_.data(), scratch_.size()));
    if (!chunk)
    {
        return tl::make_unexpected(UpgradePlanError::ChunkPlanError);
    }

    ChunkRequest request{};
    request.packet.req_id = req_id;
    request.packet.image_id = image_id_;
    request.packet.target_slot = target_slot_;
    request.packet.reserved0 = 0;
    request.packet.session_id = session_id;
    request.packet.offset = chunk->offset;
    request.packet.data_size = chunk->transmit_size;
    request.packet.reserved1 = 0;
    request.packet.chunk_crc32 = chunk->crc32;
    std::memcpy(request.packet.data,
                chunk->transmit_payload.data(),
                chunk->transmit_payload.size());
    request.valid_size = chunk->valid_size;
    return request;
}

std::uint32_t UpgradePlan::image_size() const
{
    return chunk_plan_.image_size();
}

std::uint32_t UpgradePlan::image_crc32() const
{
    return chunk_plan_.image_crc32();
}

std::uint16_t UpgradePlan::write_align() const
{
    return chunk_plan_.write_align();
}

std::uint16_t UpgradePlan::max_chunk_size() const
{
    return chunk_plan_.max_chunk_size();
}

std::size_t UpgradePlan::chunk_count() const
{
    return chunk_plan_.chunk_count();
}

std::uint8_t UpgradePlan::image_id() const
{
    return image_id_;
}

std::uint8_t UpgradePlan::target_slot() const
{
    return target_slot_;
}

UpgradePlan::UpgradePlan(const ChunkPlan& chunk_plan,
                         std::uint8_t image_id,
                         std::uint8_t target_slot)
    : chunk_plan_(chunk_plan)
    , image_id_(image_id)
    , target_slot_(target_slot)
{
}

} // namespace florid::usb::upgrade
