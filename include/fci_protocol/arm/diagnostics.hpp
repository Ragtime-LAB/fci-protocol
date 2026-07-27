#ifndef FCI_PROTOCOL_ARM_DIAGNOSTICS_HPP
#define FCI_PROTOCOL_ARM_DIAGNOSTICS_HPP

#include <cstdint>

#include "fci_protocol/arm/constants.hpp"

#pragma pack(push, 1)

namespace fci::arm {

struct JointDiag {
    std::uint8_t healthy;
};

struct GripperDiag {
    std::uint8_t healthy;
};

struct ArmDiagnostics {
    std::uint32_t uptime_s;
    std::uint32_t tick_count;
    std::uint32_t mode_entry_ms;
    std::uint8_t bus_healthy;
    std::uint8_t bus_state;
    std::uint16_t tx_err_count;
    std::uint16_t rx_err_count;
    JointDiag joints[6];
    GripperDiag gripper;
};

} // namespace fci::arm

#pragma pack(pop)

#endif // FCI_PROTOCOL_ARM_DIAGNOSTICS_HPP
