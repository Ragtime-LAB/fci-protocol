#ifndef FLORID_USB_PROTOCOL_UPGRADE_BUILDER_HPP
#define FLORID_USB_PROTOCOL_UPGRADE_BUILDER_HPP

#include "florid_usb_protocol/upgrade/chunk_plan.hpp"
#include "florid_usb_protocol/upgrade/packets.hpp"

#include <array>
#include <cstddef>
#include <cstdint>

#include "tl/expected.hpp"

namespace florid::usb::upgrade {

enum class UpgradePlanError : std::uint8_t {
    InvalidImageId = 0,
    InvalidTargetSlot = 1,
    InvalidSessionId = 2,
    ChunkPlanError = 3,
    ScratchTooSmall = 4,
};

struct ChunkRequest {
    WriteChunkRequest packet{};
};

class UpgradePlan {
public:
    static tl::expected<UpgradePlan, UpgradePlanError> create(
        const FirmwareImage& image,
        std::uint16_t write_align,
        std::uint16_t max_chunk_size,
        std::uint8_t image_id = to_u8(ImageId::Application),
        std::uint8_t target_slot = to_u8(SlotId::Secondary));

    StartUpgradeRequest make_start_request(
        std::uint8_t req_id,
        std::uint8_t flags = to_u8(StartUpgradeFlags::None)) const;

    FinishUpgradeRequest make_finish_request(std::uint8_t req_id,
                                             std::uint32_t session_id) const;

    SetPendingRequest make_set_pending_request(
        std::uint8_t req_id,
        std::uint8_t flags = to_u8(SetPendingFlags::None)) const;

    RebootRequest make_reboot_request(
        std::uint8_t req_id,
        std::uint8_t mode = to_u8(RebootMode::Normal)) const;

    tl::expected<ChunkRequest, UpgradePlanError> make_chunk_request(
        std::size_t index,
        std::uint8_t req_id,
        std::uint32_t session_id) const;

    std::uint32_t image_size() const;
    std::uint32_t image_crc32() const;
    std::uint16_t write_align() const;
    std::uint16_t max_chunk_size() const;
    std::size_t chunk_count() const;
    std::uint8_t image_id() const;
    std::uint8_t target_slot() const;

private:
    UpgradePlan(const ChunkPlan& chunk_plan,
                std::uint8_t image_id,
                std::uint8_t target_slot);

    ChunkPlan chunk_plan_;
    std::uint8_t image_id_ = to_u8(ImageId::Application);
    std::uint8_t target_slot_ = to_u8(SlotId::Secondary);
    mutable std::array<std::uint8_t, kWriteChunkPayloadBytes> scratch_{};
};

} // namespace florid::usb::upgrade

#endif // FLORID_USB_PROTOCOL_UPGRADE_BUILDER_HPP
