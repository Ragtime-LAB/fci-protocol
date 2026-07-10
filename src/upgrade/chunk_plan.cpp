#include "florid_usb_protocol/upgrade/chunk_plan.hpp"

#include "florid_usb_protocol/upgrade/crc.hpp"

#include <algorithm>
#include <cstring>

namespace florid::usb::upgrade {

namespace {

constexpr std::uint8_t kFlashErasedValue = 0xFF;

} // namespace

std::uint32_t align_up(std::uint32_t value, std::uint32_t alignment)
{
    if (alignment == 0)
    {
        return value;
    }

    const auto remainder = value % alignment;
    return remainder == 0 ? value : (value + alignment - remainder);
}

bool is_aligned(std::uint32_t value, std::uint32_t alignment)
{
    return alignment != 0 && (value % alignment) == 0;
}

tl::expected<ChunkPlan, ChunkPlanError> ChunkPlan::create(
    const FirmwareImage& image,
    std::uint16_t write_align,
    std::uint16_t max_chunk_size)
{
    if (write_align == 0)
    {
        return tl::make_unexpected(ChunkPlanError::InvalidWriteAlign);
    }
    if (max_chunk_size == 0)
    {
        return tl::make_unexpected(ChunkPlanError::InvalidChunkSize);
    }
    if (!is_aligned(max_chunk_size, write_align))
    {
        return tl::make_unexpected(ChunkPlanError::ChunkSizeNotAligned);
    }
    if (image.size() == 0)
    {
        return tl::make_unexpected(ChunkPlanError::ImageTooLarge);
    }

    const auto chunk_count =
        (static_cast<std::size_t>(image.size()) + max_chunk_size - 1u) / max_chunk_size;
    return ChunkPlan(image, write_align, max_chunk_size, chunk_count);
}

std::uint16_t ChunkPlan::write_align() const
{
    return write_align_;
}

std::uint16_t ChunkPlan::max_chunk_size() const
{
    return max_chunk_size_;
}

std::uint32_t ChunkPlan::image_size() const
{
    return image_->size();
}

std::uint32_t ChunkPlan::image_crc32() const
{
    return image_->crc32();
}

std::size_t ChunkPlan::chunk_count() const
{
    return chunk_count_;
}

tl::expected<ChunkView, ChunkPlanError> ChunkPlan::chunk_at(
    std::size_t index,
    std::span<std::uint8_t> scratch) const
{
    if (index >= chunk_count_)
    {
        return tl::make_unexpected(ChunkPlanError::ChunkIndexOutOfRange);
    }
    if (scratch.size() < max_chunk_size_)
    {
        return tl::make_unexpected(ChunkPlanError::InvalidChunkSize);
    }

    const auto offset = static_cast<std::uint32_t>(index * max_chunk_size_);
    const auto remaining = image_->size() - offset;
    const auto valid_size = static_cast<std::uint16_t>(
        std::min<std::uint32_t>(remaining, max_chunk_size_));
    const auto transmit_size = static_cast<std::uint16_t>(
        align_up(valid_size, write_align_));

    auto valid_payload = image_->subspan(offset, valid_size);
    if (valid_payload.empty())
    {
        return tl::make_unexpected(ChunkPlanError::ChunkIndexOutOfRange);
    }

    auto tx_payload = scratch.first(transmit_size);
    std::memset(tx_payload.data(), kFlashErasedValue, tx_payload.size());
    std::memcpy(tx_payload.data(), valid_payload.data(), valid_payload.size());

    ChunkView view{};
    view.offset = offset;
    view.valid_size = valid_size;
    view.transmit_size = transmit_size;
    view.crc32 = compute_crc32(tx_payload);
    view.valid_payload = valid_payload;
    view.transmit_payload = tx_payload;
    return view;
}

ChunkPlan::ChunkPlan(const FirmwareImage& image,
                     std::uint16_t write_align,
                     std::uint16_t max_chunk_size,
                     std::size_t chunk_count)
    : image_(&image)
    , write_align_(write_align)
    , max_chunk_size_(max_chunk_size)
    , chunk_count_(chunk_count)
{
}

} // namespace florid::usb::upgrade
