#ifndef FCI_PROTOCOL_ARM_PACKETS_HPP
#define FCI_PROTOCOL_ARM_PACKETS_HPP

#include "fci_protocol/arm/constants.hpp"
#include "fci_protocol/arm/device_info.hpp"
#include "RPL/Meta/PacketTraits.hpp"
#include "RPL/Packets/USBAck.hpp"

#include <cstddef>
#include <cstdint>
#include <array>

#pragma pack(push, 1)

namespace fci::arm {

// ──────────────────────────────────────────────
//  Telemetry (firmware → host)
// ──────────────────────────────────────────────

struct JointStatus {
    std::array<float, 6> q;
    std::array<float, 6> dq;
    std::array<float, 6> tau;
};

struct GripperStatus {
    float q;
    float dq;
    float tau;
};

struct ArmStatus {
    ArmMode mode;
    std::uint32_t seq;
    std::uint64_t timestamp_us;
    JointStatus status;
    float base_gravity[3];
    GripperStatus gripper;
    float O_T_EE[16];       // end-effector pose (column-major 4x4), omni-float for single-precision
    float F_ext[6];          // estimated external wrench (Fx,Fy,Fz,Mx,My,Mz)
    std::uint32_t errors;    // error bitmap
    std::uint64_t last_sdk_timestamp_us; // echo: most recent control packet's sdk timestamp
};

struct MotorFeedback {
    std::uint8_t joint_id : 3;
    std::uint8_t device_status : 4; // 0=ok, 1=warn, 2=error
    std::uint8_t enabled : 1;
    float position_rad;
    float speed_rad_s;
    float torque_nm;
    float temp_c;
};

struct MotorFeedbackArray {
    MotorFeedback motors[7];
};

// ──────────────────────────────────────────────
//  Ack
// ──────────────────────────────────────────────

struct AckPacket {
    ReqId req_id;
    std::uint16_t cmd_id;
    std::uint8_t status;
};

// ──────────────────────────────────────────────
//  Command payloads (request body)
// ──────────────────────────────────────────────

struct ArmControlModeCommand {
    MotorControlMode mode;
};

struct GripperControlModeCommand {
    MotorControlMode mode;
};

struct SetArmModeCommand {
    ArmMode mode;
};

struct SetZeroCommand {
    std::uint8_t joint_id;
};

struct ClearErrorCommand {
    std::uint8_t joint_id;
};

struct HomeAllCommand {
    std::uint8_t dummy;
};

struct ClearFaultsCommand {
    std::uint8_t dummy;
};

struct SdkClientConnectedCommand {
    std::uint8_t dummy;
};

struct SdkClientDisconnectedCommand {
    std::uint8_t dummy;
};

struct GetMotorFeedbackCommand {
    std::uint8_t dummy;
};

// ──────────────────────────────────────────────
//  Response payloads
// ──────────────────────────────────────────────








struct GetMotorFeedbackResponse {
    MotorFeedbackArray motors;
};

// ──────────────────────────────────────────────
//  Request packets (host → firmware)
// ──────────────────────────────────────────────

struct ArmControlModeRequestPacket {
    ReqId req_id;
    ArmControlModeCommand payload;
};

struct GripperControlModeRequestPacket {
    ReqId req_id;
    GripperControlModeCommand payload;
};

struct SetArmModeRequestPacket {
    ReqId req_id;
    SetArmModeCommand payload;
};

struct SetZeroRequestPacket {
    ReqId req_id;
    SetZeroCommand payload;
};

struct ClearErrorRequestPacket {
    ReqId req_id;
    ClearErrorCommand payload;
};

struct HomeAllRequestPacket {
    ReqId req_id;
    HomeAllCommand payload;
};

struct ClearFaultsRequestPacket {
    ReqId req_id;
    ClearFaultsCommand payload;
};

struct SdkClientConnectedRequestPacket {
    ReqId req_id;
    SdkClientConnectedCommand payload;
};

struct SdkClientDisconnectedRequestPacket {
    ReqId req_id;
    SdkClientDisconnectedCommand payload;
};

struct GetMotorFeedbackRequestPacket {
    ReqId req_id;
    GetMotorFeedbackCommand payload;
};

// ──────────────────────────────────────────────
//  Response packets (firmware → host)
// ──────────────────────────────────────────────









struct GetMotorFeedbackResponsePacket {
    ReqId req_id;
    GetMotorFeedbackResponse payload;
};

// ──────────────────────────────────────────────
//  Real-time control (fire-and-forget, no tx_id)
// ──────────────────────────────────────────────

struct JointMITCommandPacket {
    float q[6];
    float dq[6];
    float tau[6];
    float kp[6];
    float kd[6];
    std::uint32_t dt_us;
    std::uint16_t seq;
    std::uint8_t control_mode;
    std::uint64_t sdk_timestamp_us; // host monotonic timestamp when packet was sent
};

struct JointPosVelCommandPacket {
    float q[6];
    float dq[6];
    std::uint8_t enabled_mask;
    std::uint16_t seq;
    std::uint64_t sdk_timestamp_us;
};

struct JointVelCommandPacket {
    float dq[6];
    std::uint8_t enabled_mask;
    std::uint16_t seq;
    std::uint64_t sdk_timestamp_us;
};

struct JointPVTCommandPacket {
    float q[6];
    float dq_limit[6];
    float current_limit_norm[6];
    std::uint8_t enabled_mask;
    std::uint16_t seq;
    std::uint64_t sdk_timestamp_us;
};

struct CartesianPoseCommandPacket {
    float T[16];
    float kp[6];
    float kd[6];
    std::uint32_t dt_us;
    std::uint16_t seq;
    std::uint8_t control_mode;
    std::uint64_t sdk_timestamp_us;
};

struct CartesianVelocityCommandPacket {
    float v[6];
    float kp[6];
    float kd[6];
    std::uint32_t dt_us;
    std::uint16_t seq;
    std::uint8_t control_mode;
    std::uint64_t sdk_timestamp_us;
};

struct EmergencyStopPacket {
    std::uint8_t dummy;
};

struct GripperCommandPacket {
    float q;
    float dq;
    float tau;
    float kp;
    float kd;
    std::uint32_t dt_us;
    std::uint16_t seq;
    std::uint8_t control_mode;
    std::uint64_t sdk_timestamp_us;
};

struct GripperPosVelCommandPacket {
    float q;
    float dq;
    std::uint16_t seq;
    std::uint64_t sdk_timestamp_us;
};

struct GripperVelCommandPacket {
    float dq;
    std::uint16_t seq;
    std::uint64_t sdk_timestamp_us;
};

struct GripperPVTCommandPacket {
    float q;
    float dq_limit;
    float current_limit_norm;
    std::uint16_t seq;
    std::uint64_t sdk_timestamp_us;
};

} // namespace fci::arm

// ══════════════════════════════════════════════
//  RPL PacketTraits specialisations
// ══════════════════════════════════════════════

namespace RPL::Meta {

template <>
struct PacketTraits<fci::arm::ArmStatus>
    : PacketTraitsBase<PacketTraits<fci::arm::ArmStatus>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::ArmStatus);
    static constexpr std::size_t size = sizeof(fci::arm::ArmStatus);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::MotorFeedbackArray>
    : PacketTraitsBase<PacketTraits<fci::arm::MotorFeedbackArray>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::MotorFeedbackArray);
    static constexpr std::size_t size = sizeof(fci::arm::MotorFeedbackArray);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::GripperStatus>
    : PacketTraitsBase<PacketTraits<fci::arm::GripperStatus>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GripperStatus);
    static constexpr std::size_t size = sizeof(fci::arm::GripperStatus);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::AckPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::AckPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::Ack);
    static constexpr std::size_t size = sizeof(fci::arm::AckPacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Ack;
};

template <>
struct PacketTraits<fci::arm::ArmControlModeRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::ArmControlModeRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::ArmControlModeRequest);
    static constexpr std::size_t size = sizeof(fci::arm::ArmControlModeRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::GripperControlModeRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GripperControlModeRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GripperControlModeRequest);
    static constexpr std::size_t size = sizeof(fci::arm::GripperControlModeRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetArmModeRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetArmModeRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetArmModeRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetArmModeRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetZeroRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetZeroRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetZeroRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetZeroRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::ClearErrorRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::ClearErrorRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::ClearErrorRequest);
    static constexpr std::size_t size = sizeof(fci::arm::ClearErrorRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::HomeAllRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::HomeAllRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::HomeAllRequest);
    static constexpr std::size_t size = sizeof(fci::arm::HomeAllRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::ClearFaultsRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::ClearFaultsRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::ClearFaultsRequest);
    static constexpr std::size_t size = sizeof(fci::arm::ClearFaultsRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SdkClientConnectedRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SdkClientConnectedRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SdkClientConnectedRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SdkClientConnectedRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SdkClientDisconnectedRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SdkClientDisconnectedRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SdkClientDisconnectedRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SdkClientDisconnectedRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::GetMotorFeedbackRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GetMotorFeedbackRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GetMotorFeedbackRequest);
    static constexpr std::size_t size = sizeof(fci::arm::GetMotorFeedbackRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::GetMotorFeedbackResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GetMotorFeedbackResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GetMotorFeedbackResponse);
    static constexpr std::size_t size = sizeof(fci::arm::GetMotorFeedbackResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::JointMITCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::JointMITCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::JointMITCommand);
    static constexpr std::size_t size = sizeof(fci::arm::JointMITCommandPacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::EmergencyStopPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::EmergencyStopPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::EmergencyStop);
    static constexpr std::size_t size = sizeof(fci::arm::EmergencyStopPacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::GripperCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GripperCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GripperCommand);
    static constexpr std::size_t size = sizeof(fci::arm::GripperCommandPacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::JointPosVelCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::JointPosVelCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::JointPosVelCommand);
    static constexpr std::size_t size = sizeof(fci::arm::JointPosVelCommandPacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::JointVelCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::JointVelCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::JointVelCommand);
    static constexpr std::size_t size = sizeof(fci::arm::JointVelCommandPacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::JointPVTCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::JointPVTCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::JointPVTCommand);
    static constexpr std::size_t size = sizeof(fci::arm::JointPVTCommandPacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::GetDeviceInfoRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GetDeviceInfoRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GetDeviceInfoRequest);
    static constexpr std::size_t size = sizeof(fci::arm::GetDeviceInfoRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::GetDeviceInfoResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GetDeviceInfoResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GetDeviceInfoResponse);
    static constexpr std::size_t size = sizeof(fci::arm::GetDeviceInfoResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::SetDeviceInfoRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetDeviceInfoRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetDeviceInfoRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetDeviceInfoRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::CartesianPoseCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::CartesianPoseCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::CartesianPoseCommand);
    static constexpr std::size_t size = sizeof(fci::arm::CartesianPoseCommandPacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::CartesianVelocityCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::CartesianVelocityCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::CartesianVelocityCommand);
    static constexpr std::size_t size = sizeof(fci::arm::CartesianVelocityCommandPacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::GripperPosVelCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GripperPosVelCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GripperPosVelCommand);
    static constexpr std::size_t size = sizeof(fci::arm::GripperPosVelCommandPacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::GripperVelCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GripperVelCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GripperVelCommand);
    static constexpr std::size_t size = sizeof(fci::arm::GripperVelCommandPacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::GripperPVTCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GripperPVTCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GripperPVTCommand);
    static constexpr std::size_t size = sizeof(fci::arm::GripperPVTCommandPacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

} // namespace RPL::Meta

#pragma pack(pop)

#endif // FCI_PROTOCOL_ARM_PACKETS_HPP
