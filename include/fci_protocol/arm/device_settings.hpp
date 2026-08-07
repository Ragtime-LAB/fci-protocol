#ifndef FCI_PROTOCOL_ARM_DEVICE_SETTINGS_HPP
#define FCI_PROTOCOL_ARM_DEVICE_SETTINGS_HPP

#include <cstdint>
#include <array>
#include <utility>

#include "fci_protocol/arm/constants.hpp"

#pragma pack(push, 1)

namespace fci::arm
{
    // ──────────────────────────────────────────────
    //  Per-motor torque folding parameters
    // ──────────────────────────────────────────────

    struct TorqueFoldParams
    {
        float t_cont; // continuous allowed torque (no overheating)
        float t_peak; // peak allowed torque (full torque)
        float thermal_capacity; // thermal capacity threshold (how long peak torque can be sustained)
    };

    // ──────────────────────────────────────────────
    //  Device settings (bidirectional)
    // ──────────────────────────────────────────────

    struct DeviceSettings
    {
        std::uint32_t firmware_dt_us;       // control period in us (e.g. 2000 = 500 Hz)
        std::array<float, 6> gravity_scale; // gravity compensation scale per joint
        std::array<TorqueFoldParams, 7> torque_fold; // torque folding params for 6 joints + 1 claw
        std::array<std::pair<float, float>, 6> joint_limits; // [min, max] rad per joint
    };

    // ──────────────────────────────────────────────
    //  Request / response payloads
    // ──────────────────────────────────────────────

    struct GetDeviceSettingsCommand
    {
        std::uint8_t dummy;
    };

    struct GetDeviceSettingsResponse
    {
        DeviceSettings settings;
    };

    struct SetDeviceSettingsCommand
    {
        DeviceSettings settings;
    };

    enum class SetDeviceSettingsStatus : std::uint8_t
    {
        Ok = 0,
        StorageFailed = 1,
    };

    // ──────────────────────────────────────────────
    //  Request / response packets
    // ──────────────────────────────────────────────

    struct GetDeviceSettingsRequestPacket
    {
        ReqId req_id;
        GetDeviceSettingsCommand payload;
    };

    struct GetDeviceSettingsResponsePacket
    {
        ReqId req_id;
        GetDeviceSettingsResponse payload;
    };

    struct SetDeviceSettingsRequestPacket
    {
        ReqId req_id;
        SetDeviceSettingsCommand payload;
    };
} // namespace fci::arm

#pragma pack(pop)

#endif // FCI_PROTOCOL_ARM_DEVICE_SETTINGS_HPP
