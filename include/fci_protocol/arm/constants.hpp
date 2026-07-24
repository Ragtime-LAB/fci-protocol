#ifndef FCI_PROTOCOL_ARM_CONSTANTS_HPP
#define FCI_PROTOCOL_ARM_CONSTANTS_HPP

#include <cstdint>

#include "fci_protocol/version.hpp"

namespace fci::arm
{
    using ReqId = std::uint8_t;

    inline constexpr fci::Semver kProtocolVersion = fci::MakeSemver(0, 0, 1);

    enum class Command : std::uint16_t
    {
        // ── Telemetry (firmware → host, notification) ──
        ArmStatus = 0x6001,
        MotorFeedbackArray = 0x6002,
        GripperStatus = 0x6003,

        // ── Ack ──
        Ack = 0x6FF0,

        // ── Reliable requests (response via Ack status) ──
        SetZeroRequest = 0x6107,
        ClearErrorRequest = 0x6109,
        HomeAllRequest = 0x6201,
        ClearFaultsRequest = 0x6205,
        SdkClientConnectedRequest = 0x6209,
        SdkClientDisconnectedRequest = 0x620B,
        GetMotorFeedbackRequest = 0x6213,
        GetDeviceInfoRequest = 0x6215,
        SetDeviceInfoRequest = 0x6217,
        ArmControlModeRequest = 0x6219,
        GripperControlModeRequest = 0x621B,
        SetArmModeRequest = 0x6225,
        MotorRegisterReadRequest = 0x621D,
        MotorRegisterWriteRequest = 0x621F,
        MotorStoreParamsRequest = 0x6221,
        MotorSetZeroRequest = 0x6223,

        // ── Data-carrying responses (not covered by Ack) ──
        GetMotorFeedbackResponse = 0x6214,
        GetDeviceInfoResponse = 0x6216,
        MotorRegisterReadResponse = 0x621E,

        // ── Real-time control (fire-and-forget, notification) ──
        JointMITCommand = 0x6301,
        EmergencyStop = 0x6303,
        GripperCommand = 0x6305,
        JointPosVelCommand = 0x6306,
        JointVelCommand = 0x6307,
        JointPVTCommand = 0x6308,
        CartesianPoseCommand = 0x6309,
        CartesianVelocityCommand = 0x630A,
        GripperPosVelCommand = 0x6311,
        GripperVelCommand = 0x6312,
        GripperPVTCommand = 0x6313,
    };

    enum class MotorStateValue : std::uint8_t
    {
        Disable = 0,
        Enable = 1,
    };

    enum class MotorControlMode : std::uint8_t
    {
        MIT = 1,
        PosVel = 2,
        Vel = 3,
        PVT = 4,
    };

    enum class FirmwareType : std::uint8_t
    {
        StandardArm = 0,
        MobileArm = 1,
        CobotArm = 2,
    };

    enum class ArmMode : std::uint8_t
    {
        Pc = 0,
        Drag = 1,
        Damp = 2,
        Retracting = 3,
    };

    // Ack status — unified across all Request packets
    enum class AckStatus : std::uint8_t
    {
        Ok = 0,
        Failed = 1,
    };

    enum class MotorRegisterStatus : std::uint8_t
    {
        Ok = 0,
        InvalidJoint = 1,
        Timeout = 2,
        NotInDampMode = 3,
    };

    constexpr std::uint16_t to_u16(Command value)
    {
        return static_cast<std::uint16_t>(value);
    }

    constexpr std::uint8_t to_u8(MotorStateValue value)
    {
        return static_cast<std::uint8_t>(value);
    }

    constexpr std::uint8_t to_u8(MotorControlMode value)
    {
        return static_cast<std::uint8_t>(value);
    }

    constexpr std::uint8_t to_u8(FirmwareType value)
    {
        return static_cast<std::uint8_t>(value);
    }

    constexpr std::uint8_t to_u8(ArmMode value)
    {
        return static_cast<std::uint8_t>(value);
    }
} // namespace fci::arm

#endif // FCI_PROTOCOL_ARM_CONSTANTS_HPP
