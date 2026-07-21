#ifndef FCI_PROTOCOL_MESSAGE_ARM_CONTROL_HPP
#define FCI_PROTOCOL_MESSAGE_ARM_CONTROL_HPP

#include <array>
#include <cstdint>
#include <type_traits>

namespace fci::message::arm_control {

enum class ModeRequestType : std::uint8_t {
    None = 0,
    Damp,
    Drag,
    Home,
    Pc,
    PowerOff,
    Estop,
    StopPcControl,
};

enum class ModeRequestPriority : std::uint8_t {
    Low = 0,
    Normal,
    High,
    Critical,
};

enum class PcControlKind : std::uint8_t {
    None = 0,
    MIT,
    MitGravity,
    PosVel,
    Velocity,
    PVT,
};

enum class SessionEventType : std::uint8_t {
    None = 0,
    TransportConnected,
    TransportDisconnected,
    SessionStart,
    SessionStop,
    HeartbeatTimeout,
};

enum class CommandKind : std::uint8_t {
    None = 0,
    ModeRequest,
    JointCommand,
    GripperCommand,
    SessionEvent,
};

struct ModeCommand {
    ModeRequestType type{ModeRequestType::None};
    ModeRequestPriority priority{ModeRequestPriority::Low};
    std::uint8_t flags{0};
};

struct SessionCommand {
    SessionEventType type{SessionEventType::None};
    std::uint8_t flags{0};
};

struct JointCommand {
    PcControlKind control_kind{PcControlKind::None};
    std::uint8_t flags{0};
    std::uint16_t dt_us{0};
    std::array<float, 6> q{};
    std::array<float, 6> dq{};
    std::array<float, 6> tau{};
    std::array<float, 6> kp{};
    std::array<float, 6> kd{};
    std::array<float, 6> aux{};
};

struct GripperCommand {
    float q{0.0f};
    float dq{0.0f};
    float tau{0.0f};
    std::uint8_t flags{0};
};

struct ArmCommandMsg {
    CommandKind kind{CommandKind::None};
    std::uint8_t reserved[3]{};
    ModeCommand mode{};
    SessionCommand session{};
    JointCommand joint{};
    GripperCommand gripper{};
};

static_assert(std::is_trivially_copyable_v<ArmCommandMsg>,
              "ArmCommandMsg must stay trivially copyable");

} // namespace fci::message::arm_control

#endif // FCI_PROTOCOL_MESSAGE_ARM_CONTROL_HPP
