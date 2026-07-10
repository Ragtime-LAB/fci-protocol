#include "florid_usb_protocol/upgrade/image.hpp"

#include "florid_usb_protocol/upgrade/crc.hpp"

#include <limits>

namespace florid::usb::upgrade {

tl::expected<FirmwareImage, ImageError> FirmwareImage::from_bytes(
    std::span<const std::uint8_t> bytes)
{
    if (bytes.empty())
    {
        return tl::make_unexpected(ImageError::Empty);
    }
    if (bytes.size() > static_cast<std::size_t>(std::numeric_limits<std::uint32_t>::max()))
    {
        return tl::make_unexpected(ImageError::SizeTooLarge);
    }

    return FirmwareImage(bytes, compute_crc32(bytes));
}

std::span<const std::uint8_t> FirmwareImage::bytes() const
{
    return bytes_;
}

std::span<const std::uint8_t> FirmwareImage::subspan(std::uint32_t offset,
                                                     std::uint32_t size) const
{
    const auto end = static_cast<std::uint64_t>(offset) + static_cast<std::uint64_t>(size);
    if (end > bytes_.size())
    {
        return {};
    }

    return bytes_.subspan(offset, size);
}

std::uint32_t FirmwareImage::size() const
{
    return static_cast<std::uint32_t>(bytes_.size());
}

std::uint32_t FirmwareImage::crc32() const
{
    return crc32_;
}

FirmwareImage::FirmwareImage(std::span<const std::uint8_t> bytes, std::uint32_t crc32)
    : bytes_(bytes)
    , crc32_(crc32)
{
}

} // namespace florid::usb::upgrade
