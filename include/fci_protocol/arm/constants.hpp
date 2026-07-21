#ifndef FCI_PROTOCOL_ARM_CONSTANTS_HPP
#define FCI_PROTOCOL_ARM_CONSTANTS_HPP

#include <cstdint>

#include "fci_protocol/version.hpp"

namespace fci::arm
{
    using TransactionId = std::uint32_t;

    inline constexpr fci::Semver kProtocolVersion = fci::MakeSemver(0, 0, 1);

    enum class Command : std::uint16_t
    {
        // ── Telemetry (firmware → host, notification) ──
        ArmStatus = 0x6001,
        MotorFeedbackArray = 0x6002,
        GripperStatus = 0x6003,

        // ── Ack ──
        Ack = 0x6FF0,

        // ── Reliable request / response pairs ──
        SetMitLimitRequest = 0x6103,
        SetMitLimitResponse = 0x6104,
        SetMotorStateRequest = 0x6105,
        SetMotorStateResponse = 0x6106,
        SetZeroRequest = 0x6107,
        SetZeroResponse = 0x6108,
        ClearErrorRequest = 0x6109,
        ClearErrorResponse = 0x610A,
        HomeAllRequest = 0x6201,
        HomeAllResponse = 0x6202,
        RunCalibrationRequest = 0x6203,
        RunCalibrationResponse = 0x6204,
        ClearFaultsRequest = 0x6205,
        ClearFaultsResponse = 0x6206,
        SetSafetyRequest = 0x6207,
        SetSafetyResponse = 0x6208,
        SdkClientConnectedRequest = 0x6209,
        SdkClientConnectedResponse = 0x620A,
        SdkClientDisconnectedRequest = 0x620B,
        SdkClientDisconnectedResponse = 0x620C,
        HomeDoneRequest = 0x620D,
        HomeDoneResponse = 0x620E,
        UsbSessionStartRequest = 0x620F,
        UsbSessionStartResponse = 0x6210,
        UsbSessionStopRequest = 0x6211,
        UsbSessionStopResponse = 0x6212,
        GetMotorFeedbackRequest = 0x6213,
        GetMotorFeedbackResponse = 0x6214,
        GetDeviceInfoRequest = 0x6215,
        GetDeviceInfoResponse = 0x6216,
        SetDeviceInfoRequest = 0x6217,
        SetDeviceInfoResponse = 0x6218,
        SetMotorControlModeRequest = 0x6219,
        SetMotorControlModeResponse = 0x621A,
        SetJointImpedanceRequest = 0x621B,
        SetJointImpedanceResponse = 0x621C,
        SetCartesianImpedanceRequest = 0x621D,
        SetCartesianImpedanceResponse = 0x621E,
        SetEEFrameRequest = 0x621F,
        SetEEFrameResponse = 0x6220,
        SetLoadRequest = 0x6221,
        SetLoadResponse = 0x6222,
        StartMotionRequest = 0x6223,
        StartMotionResponse = 0x6224,
        StopMotionRequest = 0x6225,
        StopMotionResponse = 0x6226,

        // ── Real-time control (fire-and-forget, notification) ──
        JointCommand = 0x6301,
        EmergencyStop = 0x6303,
        GripperCommand = 0x6305,
        JointPosVelCommand = 0x6306,
        JointVelocityCommand = 0x6307,
        JointHybridCommand = 0x6308,
        CartesianPoseCommand = 0x6309,
        CartesianVelocityCommand = 0x630A,
    };

    // ── Overall arm FSM ──
    enum class ArmMode : std::uint8_t
    {
        Init = 0,
        Idle = 1,
        Running = 2,
        Fault = 3,
        EStop = 4,
    };

    enum class SetMitLimitStatus : std::uint8_t
    {
        Ok = 0,
        InvalidJoint = 1,
        StorageFailed = 2,
    };

    enum class MotorStateValue : std::uint8_t
    {
        Disable = 0,
        Enable = 1,
    };

    enum class SetMotorStateStatus : std::uint8_t
    {
        Ok = 0,
        UnsupportedInCurrentMode = 1,
        InvalidJoint = 2,
        StorageFailed = 3,
    };

    enum class MotorControlMode : std::uint8_t
    {
        Mit = 1,
        PosVel = 2,
        Vel = 3,
        Hybrid = 4,
    };

    enum class SetMotorControlModeStatus : std::uint8_t
    {
        Ok = 0,
        UnsupportedInCurrentMode = 1,
        InvalidJoint = 2,
        InvalidMode = 3,
        CanTxFailed = 4,
    };

    enum class SetZeroStatus : std::uint8_t
    {
        Ok = 0,
        InvalidJoint = 1,
        CalibrationFailed = 2,
    };

    enum class ClearErrorStatus : std::uint8_t
    {
        Ok = 0,
        InvalidJoint = 1,
    };

    enum class HomeAllStatus : std::uint8_t
    {
        Ok = 0,
        NotIdle = 1,
        CalibrationFailed = 2,
    };

    enum class CalibrationType : std::uint8_t
    {
        Home = 0,
        Zero = 1,
    };

    enum class RunCalibrationStatus : std::uint8_t
    {
        Ok = 0,
        NotIdle = 1,
        CalibrationFailed = 2,
    };

    enum class ClearFaultsStatus : std::uint8_t
    {
        Ok = 0,
    };

    enum class FirmwareType : std::uint8_t
    {
        StandardArm = 0,
        MobileArm = 1,
        CobotArm = 2,
    };

    enum class CollisionSensitivity : std::uint8_t
    {
        Low = 0,
        Medium = 1,
        High = 2,
    };

    enum class SetSafetyStatus : std::uint8_t
    {
        Ok = 0,
        StorageFailed = 1,
    };

    enum class SdkClientNotifyStatus : std::uint8_t
    {
        Ok = 0,
    };

    enum class HomeDoneStatus : std::uint8_t
    {
        Ok = 0,
    };

    enum class UsbSessionStartStatus : std::uint8_t
    {
        Ok = 0,
    };

    enum class UsbSessionStopStatus : std::uint8_t
    {
        Ok = 0,
    };

    enum class StartMotionStatus : std::uint8_t
    {
        Ok = 0,
        Busy = 1,
        InvalidMode = 2,
        NotIdle = 3,
    };

    enum class StopMotionStatus : std::uint8_t
    {
        Ok = 0,
    };

    enum class SetJointImpedanceStatus : std::uint8_t
    {
        Ok = 0,
        StorageFailed = 1,
    };

    enum class SetCartesianImpedanceStatus : std::uint8_t
    {
        Ok = 0,
        StorageFailed = 1,
    };

    enum class SetEEFrameStatus : std::uint8_t
    {
        Ok = 0,
        StorageFailed = 1,
    };

    enum class SetLoadStatus : std::uint8_t
    {
        Ok = 0,
        StorageFailed = 1,
    };

    constexpr std::uint16_t to_u16(Command value)
    {
        return static_cast<std::uint16_t>(value);
    }

    constexpr std::uint8_t to_u8(ArmMode value)
    {
        return static_cast<std::uint8_t>(value);
    }

    constexpr std::uint8_t to_u8(MotorStateValue value)
    {
        return static_cast<std::uint8_t>(value);
    }

    constexpr std::uint8_t to_u8(MotorControlMode value)
    {
        return static_cast<std::uint8_t>(value);
    }

    constexpr std::uint8_t to_u8(CalibrationType value)
    {
        return static_cast<std::uint8_t>(value);
    }

    constexpr std::uint8_t to_u8(FirmwareType value)
    {
        return static_cast<std::uint8_t>(value);
    }

    constexpr std::uint8_t to_u8(CollisionSensitivity value)
    {
        return static_cast<std::uint8_t>(value);
    }
} // namespace fci::arm

#endif // FCI_PROTOCOL_ARM_CONSTANTS_HPP
