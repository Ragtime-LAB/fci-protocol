#ifndef FLORID_USB_PROTOCOL_UPGRADE_CRC_HPP
#define FLORID_USB_PROTOCOL_UPGRADE_CRC_HPP

#include <cstddef>
#include <cstdint>
#include <span>

namespace florid::usb::upgrade {

std::uint32_t compute_crc32(std::span<const std::uint8_t> bytes);

} // namespace florid::usb::upgrade

#endif // FLORID_USB_PROTOCOL_UPGRADE_CRC_HPP
