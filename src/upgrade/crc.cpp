#include "florid_usb_protocol/upgrade/crc.hpp"

#include "cppcrc.h"

namespace florid::usb::upgrade {

std::uint32_t compute_crc32(std::span<const std::uint8_t> bytes)
{
    return CRC32::CRC32::calc(bytes.data(), bytes.size());
}

} // namespace florid::usb::upgrade
