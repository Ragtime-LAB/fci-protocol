#ifndef FLORID_USB_PROTOCOL_UPGRADE_IMAGE_HPP
#define FLORID_USB_PROTOCOL_UPGRADE_IMAGE_HPP

#include <cstddef>
#include <cstdint>
#include <span>

#include "tl/expected.hpp"

namespace florid::usb::upgrade {

enum class ImageError : std::uint8_t {
    Empty = 0,
    SizeTooLarge = 1,
    OutOfRange = 2,
};

class FirmwareImage {
public:
    static tl::expected<FirmwareImage, ImageError> from_bytes(
        std::span<const std::uint8_t> bytes);

    std::span<const std::uint8_t> bytes() const;
    std::span<const std::uint8_t> subspan(std::uint32_t offset,
                                          std::uint32_t size) const;

    std::uint32_t size() const;
    std::uint32_t crc32() const;

private:
    FirmwareImage(std::span<const std::uint8_t> bytes, std::uint32_t crc32);

    std::span<const std::uint8_t> bytes_;
    std::uint32_t crc32_ = 0;
};

} // namespace florid::usb::upgrade

#endif // FLORID_USB_PROTOCOL_UPGRADE_IMAGE_HPP
