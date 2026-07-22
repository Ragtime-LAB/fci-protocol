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
    std::uint8_t _pad0[3];
    std::uint32_t seq;
    std::uint64_t timestamp_us;
    JointStatus status;
    float base_gravity[3];
    GripperStatus gripper;
    float O_T_EE[16];       // end-effector pose (column-major 4x4), omni-float for single-precision
    float F_ext[6];          // estimated external wrench (Fx,Fy,Fz,Mx,My,Mz)
    std::uint32_t errors;    // error bitmap
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

struct SetMotorStateCommand {
    std::uint8_t joint_id;
    MotorStateValue state;
};

struct ArmControlModeCommand {
    MotorControlMode mode;
};

struct GripperControlModeCommand {
    MotorControlMode mode;
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

struct HomeDoneCommand {
    std::uint8_t dummy;
};

struct GetMotorFeedbackCommand {
    std::uint8_t dummy;
};

struct SetJointImpedanceCommand {
    float K[6];  // joint stiffness [Nm/rad]
};

struct SetCartesianImpedanceCommand {
    float K[6];  // Cartesian stiffness {x,y,z,roll,pitch,yaw} [N/m, Nm/rad]
};

struct SetEEFrameCommand {
    float T[16];  // NE_T_EE 4x4 column-major
};

struct SetLoadCommand {
    float mass_kg;         // payload mass
    float F_x_Cload[3];    // centre of mass in flange frame [m]
    float load_inertia[9]; // inertia matrix column-major [kg*m^2]
};

// ──────────────────────────────────────────────
//  Response payloads
// ──────────────────────────────────────────────

struct SetMotorStateResponse {
    SetMotorStateStatus status;
};

struct ArmControlModeResponse {
    ArmControlModeStatus status;
};

struct GripperControlModeResponse {
    GripperControlModeStatus status;
};

struct SetZeroResponse {
    SetZeroStatus status;
};

struct ClearErrorResponse {
    ClearErrorStatus status;
};

struct HomeAllResponse {
    HomeAllStatus status;
};

struct ClearFaultsResponse {
    ClearFaultsStatus status;
};

struct SdkClientNotifyResponse {
    SdkClientNotifyStatus status;
};

struct HomeDoneResponse {
    HomeDoneStatus status;
};

struct GetMotorFeedbackResponse {
    MotorFeedbackArray motors;
};

struct SetJointImpedanceResponse {
    SetJointImpedanceStatus status;
};

struct SetCartesianImpedanceResponse {
    SetCartesianImpedanceStatus status;
};

struct SetEEFrameResponse {
    SetEEFrameStatus status;
};

struct SetLoadResponse {
    SetLoadStatus status;
};

// ──────────────────────────────────────────────
//  Request packets (host → firmware)
// ──────────────────────────────────────────────

struct SetMotorStateRequestPacket {
    ReqId req_id;
    SetMotorStateCommand payload;
};

struct ArmControlModeRequestPacket {
    ReqId req_id;
    ArmControlModeCommand payload;
};

struct GripperControlModeRequestPacket {
    ReqId req_id;
    GripperControlModeCommand payload;
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

struct HomeDoneRequestPacket {
    ReqId req_id;
    HomeDoneCommand payload;
};

struct GetMotorFeedbackRequestPacket {
    ReqId req_id;
    GetMotorFeedbackCommand payload;
};

struct SetJointImpedanceRequestPacket {
    ReqId req_id;
    SetJointImpedanceCommand payload;
};

struct SetCartesianImpedanceRequestPacket {
    ReqId req_id;
    SetCartesianImpedanceCommand payload;
};

struct SetEEFrameRequestPacket {
    ReqId req_id;
    SetEEFrameCommand payload;
};

struct SetLoadRequestPacket {
    ReqId req_id;
    SetLoadCommand payload;
};

// ──────────────────────────────────────────────
//  Response packets (firmware → host)
// ──────────────────────────────────────────────

struct SetMotorStateResponsePacket {
    ReqId req_id;
    SetMotorStateResponse payload;
};

struct ArmControlModeResponsePacket {
    ReqId req_id;
    ArmControlModeResponse payload;
};

struct GripperControlModeResponsePacket {
    ReqId req_id;
    GripperControlModeResponse payload;
};

struct SetZeroResponsePacket {
    ReqId req_id;
    SetZeroResponse payload;
};

struct ClearErrorResponsePacket {
    ReqId req_id;
    ClearErrorResponse payload;
};

struct HomeAllResponsePacket {
    ReqId req_id;
    HomeAllResponse payload;
};

struct ClearFaultsResponsePacket {
    ReqId req_id;
    ClearFaultsResponse payload;
};

struct SdkClientConnectedResponsePacket {
    ReqId req_id;
    SdkClientNotifyResponse payload;
};

struct SdkClientDisconnectedResponsePacket {
    ReqId req_id;
    SdkClientNotifyResponse payload;
};

struct HomeDoneResponsePacket {
    ReqId req_id;
    HomeDoneResponse payload;
};

struct GetMotorFeedbackResponsePacket {
    ReqId req_id;
    GetMotorFeedbackResponse payload;
};

struct SetJointImpedanceResponsePacket {
    ReqId req_id;
    SetJointImpedanceResponse payload;
};

struct SetCartesianImpedanceResponsePacket {
    ReqId req_id;
    SetCartesianImpedanceResponse payload;
};

struct SetEEFrameResponsePacket {
    ReqId req_id;
    SetEEFrameResponse payload;
};

struct SetLoadResponsePacket {
    ReqId req_id;
    SetLoadResponse payload;
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
    std::uint8_t control_mode; // bit[1:0]=type(0=hold,1=MIT,3=torque), bit[2]=gravity_enable
};

struct JointPosVelCommandPacket {
    float q[6];
    float dq[6];
    std::uint8_t enabled_mask;
    std::uint16_t seq;
};

struct JointVelCommandPacket {
    float dq[6];
    std::uint8_t enabled_mask;
    std::uint16_t seq;
};

struct JointPVTCommandPacket {
    float q[6];
    float dq_limit[6];
    float current_limit_norm[6];
    std::uint8_t enabled_mask;
    std::uint16_t seq;
};

struct CartesianPoseCommandPacket {
    float T[16];            // O_T_EE_desired, column-major 4x4
    float kp[6];            // per-frame Cartesian stiffness
    float kd[6];            // per-frame Cartesian damping
    std::uint32_t dt_us;    // integration step for firmware-side interpolation
    std::uint16_t seq;      // monotonic sequence number
    std::uint8_t control_mode; // bit[1:0]=type (0=hold, 1=pos, 2=vel, 3=torque)
};

struct CartesianVelocityCommandPacket {
    float v[6];             // O_dP_EE_desired {vx,vy,vz,wx,wy,wz}
    float kp[6];            // per-frame Cartesian stiffness
    float kd[6];            // per-frame Cartesian damping
    std::uint32_t dt_us;    // integration step
    std::uint16_t seq;      // monotonic sequence number
    std::uint8_t control_mode;
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
struct PacketTraits<fci::arm::SetMotorStateRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetMotorStateRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetMotorStateRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetMotorStateRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetMotorStateResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetMotorStateResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetMotorStateResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetMotorStateResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
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
struct PacketTraits<fci::arm::ArmControlModeResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::ArmControlModeResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::ArmControlModeResponse);
    static constexpr std::size_t size = sizeof(fci::arm::ArmControlModeResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
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
struct PacketTraits<fci::arm::GripperControlModeResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GripperControlModeResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GripperControlModeResponse);
    static constexpr std::size_t size = sizeof(fci::arm::GripperControlModeResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
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
struct PacketTraits<fci::arm::SetZeroResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetZeroResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetZeroResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetZeroResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
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
struct PacketTraits<fci::arm::ClearErrorResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::ClearErrorResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::ClearErrorResponse);
    static constexpr std::size_t size = sizeof(fci::arm::ClearErrorResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
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
struct PacketTraits<fci::arm::HomeAllResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::HomeAllResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::HomeAllResponse);
    static constexpr std::size_t size = sizeof(fci::arm::HomeAllResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
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
struct PacketTraits<fci::arm::ClearFaultsResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::ClearFaultsResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::ClearFaultsResponse);
    static constexpr std::size_t size = sizeof(fci::arm::ClearFaultsResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
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
struct PacketTraits<fci::arm::SdkClientConnectedResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SdkClientConnectedResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SdkClientConnectedResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SdkClientConnectedResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
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
struct PacketTraits<fci::arm::SdkClientDisconnectedResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SdkClientDisconnectedResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SdkClientDisconnectedResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SdkClientDisconnectedResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::HomeDoneRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::HomeDoneRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::HomeDoneRequest);
    static constexpr std::size_t size = sizeof(fci::arm::HomeDoneRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::HomeDoneResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::HomeDoneResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::HomeDoneResponse);
    static constexpr std::size_t size = sizeof(fci::arm::HomeDoneResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
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
struct PacketTraits<fci::arm::SetDeviceInfoResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetDeviceInfoResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetDeviceInfoResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetDeviceInfoResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

// ── New: SetJointImpedance / SetCartesianImpedance / SetEEFrame / SetLoad ──

template <>
struct PacketTraits<fci::arm::SetJointImpedanceRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetJointImpedanceRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetJointImpedanceRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetJointImpedanceRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetJointImpedanceResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetJointImpedanceResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetJointImpedanceResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetJointImpedanceResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::SetCartesianImpedanceRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetCartesianImpedanceRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetCartesianImpedanceRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetCartesianImpedanceRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetCartesianImpedanceResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetCartesianImpedanceResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetCartesianImpedanceResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetCartesianImpedanceResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::SetEEFrameRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetEEFrameRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetEEFrameRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetEEFrameRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetEEFrameResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetEEFrameResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetEEFrameResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetEEFrameResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::SetLoadRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetLoadRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetLoadRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetLoadRequestPacket);
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetLoadResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetLoadResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetLoadResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetLoadResponsePacket);
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

// ── New: CartesianPoseCommand / CartesianVelocityCommand ──

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

} // namespace RPL::Meta

#pragma pack(pop)

#endif // FCI_PROTOCOL_ARM_PACKETS_HPP
