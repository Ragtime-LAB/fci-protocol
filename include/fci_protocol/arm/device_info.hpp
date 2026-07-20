#ifndef FCI_PROTOCOL_ARM_DEVICE_INFO_HPP
#define FCI_PROTOCOL_ARM_DEVICE_INFO_HPP

#include <cstdint>
#include <array>

#include "fci_protocol/arm/constants.hpp"

#pragma pack(push, 1)

namespace fci::arm {

// ──────────────────────────────────────────────
//  Device info (firmware → host)
// ──────────────────────────────────────────────

struct DeviceInfo {
    std::uint8_t protocol_version; // kProtocolVersion
    std::uint8_t hw_revision;      // PCB revision (A=0, B=1, ...)
    std::array<char, 32> board_name;
    std::array<char, 32> custom_name;
};

// ──────────────────────────────────────────────
//  Request / response payloads
// ──────────────────────────────────────────────

struct GetDeviceInfoCommand {
    std::uint8_t dummy;
};

struct GetDeviceInfoResponse {
    DeviceInfo info;
};

// ──────────────────────────────────────────────
//  Request / response packets (host → firmware)
// ──────────────────────────────────────────────

struct GetDeviceInfoRequestPacket {
    TransactionId tx_id;
    GetDeviceInfoCommand payload;
};

struct GetDeviceInfoResponsePacket {
    TransactionId tx_id;
    GetDeviceInfoResponse payload;
};

struct SetDeviceInfoCommand {
    std::array<char, 32> custom_name;
};

enum class SetDeviceInfoStatus : std::uint8_t {
    Ok = 0,
    StorageFailed = 1,
    NameTooLong = 2,
};

struct SetDeviceInfoResponse {
    SetDeviceInfoStatus status;
};

struct SetDeviceInfoRequestPacket {
    TransactionId tx_id;
    SetDeviceInfoCommand payload;
};

struct SetDeviceInfoResponsePacket {
    TransactionId tx_id;
    SetDeviceInfoResponse payload;
};

} // namespace fci::arm

#pragma pack(pop)

#endif // FCI_PROTOCOL_ARM_DEVICE_INFO_HPP
