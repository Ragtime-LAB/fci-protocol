#ifndef FLORID_USB_PROTOCOL_UPGRADE_CHUNK_PLAN_HPP
#define FLORID_USB_PROTOCOL_UPGRADE_CHUNK_PLAN_HPP

#include "florid_usb_protocol/upgrade/image.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>

#include "tl/expected.hpp"

namespace florid::usb::upgrade {

enum class ChunkPlanError : std::uint8_t {
    InvalidWriteAlign = 0,
    InvalidChunkSize = 1,
    ChunkSizeNotAligned = 2,
    ImageTooLarge = 3,
    ChunkIndexOutOfRange = 4,
};

struct ChunkView {
    std::uint32_t offset = 0;
    std::uint16_t valid_size = 0;
    std::uint16_t transmit_size = 0;
    std::uint32_t crc32 = 0;
    std::span<const std::uint8_t> valid_payload{};
    std::span<const std::uint8_t> transmit_payload{};
};

class ChunkPlan {
public:
    static tl::expected<ChunkPlan, ChunkPlanError> create(
        const FirmwareImage& image,
        std::uint16_t write_align,
        std::uint16_t max_chunk_size);

    std::uint16_t write_align() const;
    std::uint16_t max_chunk_size() const;
    std::uint32_t image_size() const;
    std::uint32_t image_crc32() const;
    std::size_t chunk_count() const;

    tl::expected<ChunkView, ChunkPlanError> chunk_at(
        std::size_t index,
        std::span<std::uint8_t> scratch) const;

private:
    ChunkPlan(const FirmwareImage& image,
              std::uint16_t write_align,
              std::uint16_t max_chunk_size,
              std::size_t chunk_count);

    const FirmwareImage* image_ = nullptr;
    std::uint16_t write_align_ = 0;
    std::uint16_t max_chunk_size_ = 0;
    std::size_t chunk_count_ = 0;
};

std::uint32_t align_up(std::uint32_t value, std::uint32_t alignment);
bool is_aligned(std::uint32_t value, std::uint32_t alignment);

} // namespace florid::usb::upgrade

#endif // FLORID_USB_PROTOCOL_UPGRADE_CHUNK_PLAN_HPP
