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
    TransactionId tx_id;
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

struct SetMotorControlModeCommand {
    std::uint8_t joint_id;
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

struct UsbSessionStartCommand {
    std::uint8_t dummy;
};

struct UsbSessionStopCommand {
    std::uint8_t dummy;
};

struct GetMotorFeedbackCommand {
    std::uint8_t dummy;
};

struct StartMotionCommand {
    std::uint8_t control_mode;     // MotorControlMode enum
    std::uint8_t motion_gen_mode;  // 0=None, 1=JointPos, 2=JointVel, 3=CartesianPos, 4=CartesianVel
    std::uint8_t controller_mode;  // 0=JointImpedance, 1=CartesianImpedance (only used when kFirmware)
    std::uint8_t computation_mode; // 0=kHost, 1=kFirmware
};

struct StopMotionCommand {
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

struct SetMotorControlModeResponse {
    SetMotorControlModeStatus status;
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

struct UsbSessionStartResponse {
    UsbSessionStartStatus status;
};

struct UsbSessionStopResponse {
    UsbSessionStopStatus status;
};

struct GetMotorFeedbackResponse {
    MotorFeedbackArray motors;
};

struct StartMotionResponse {
    StartMotionStatus status;
};

struct StopMotionResponse {
    StopMotionStatus status;
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
    TransactionId tx_id;
    SetMotorStateCommand payload;
};

struct SetMotorControlModeRequestPacket {
    TransactionId tx_id;
    SetMotorControlModeCommand payload;
};

struct SetZeroRequestPacket {
    TransactionId tx_id;
    SetZeroCommand payload;
};

struct ClearErrorRequestPacket {
    TransactionId tx_id;
    ClearErrorCommand payload;
};

struct HomeAllRequestPacket {
    TransactionId tx_id;
    HomeAllCommand payload;
};

struct ClearFaultsRequestPacket {
    TransactionId tx_id;
    ClearFaultsCommand payload;
};

struct SdkClientConnectedRequestPacket {
    TransactionId tx_id;
    SdkClientConnectedCommand payload;
};

struct SdkClientDisconnectedRequestPacket {
    TransactionId tx_id;
    SdkClientDisconnectedCommand payload;
};

struct HomeDoneRequestPacket {
    TransactionId tx_id;
    HomeDoneCommand payload;
};

struct UsbSessionStartRequestPacket {
    TransactionId tx_id;
    UsbSessionStartCommand payload;
};

struct UsbSessionStopRequestPacket {
    TransactionId tx_id;
    UsbSessionStopCommand payload;
};

struct GetMotorFeedbackRequestPacket {
    TransactionId tx_id;
    GetMotorFeedbackCommand payload;
};

struct StartMotionRequestPacket {
    TransactionId tx_id;
    StartMotionCommand payload;
};

struct StopMotionRequestPacket {
    TransactionId tx_id;
    StopMotionCommand payload;
};

struct SetJointImpedanceRequestPacket {
    TransactionId tx_id;
    SetJointImpedanceCommand payload;
};

struct SetCartesianImpedanceRequestPacket {
    TransactionId tx_id;
    SetCartesianImpedanceCommand payload;
};

struct SetEEFrameRequestPacket {
    TransactionId tx_id;
    SetEEFrameCommand payload;
};

struct SetLoadRequestPacket {
    TransactionId tx_id;
    SetLoadCommand payload;
};

// ──────────────────────────────────────────────
//  Response packets (firmware → host)
// ──────────────────────────────────────────────

struct SetMotorStateResponsePacket {
    TransactionId tx_id;
    SetMotorStateResponse payload;
};

struct SetMotorControlModeResponsePacket {
    TransactionId tx_id;
    SetMotorControlModeResponse payload;
};

struct SetZeroResponsePacket {
    TransactionId tx_id;
    SetZeroResponse payload;
};

struct ClearErrorResponsePacket {
    TransactionId tx_id;
    ClearErrorResponse payload;
};

struct HomeAllResponsePacket {
    TransactionId tx_id;
    HomeAllResponse payload;
};

struct ClearFaultsResponsePacket {
    TransactionId tx_id;
    ClearFaultsResponse payload;
};

struct SdkClientConnectedResponsePacket {
    TransactionId tx_id;
    SdkClientNotifyResponse payload;
};

struct SdkClientDisconnectedResponsePacket {
    TransactionId tx_id;
    SdkClientNotifyResponse payload;
};

struct HomeDoneResponsePacket {
    TransactionId tx_id;
    HomeDoneResponse payload;
};

struct UsbSessionStartResponsePacket {
    TransactionId tx_id;
    UsbSessionStartResponse payload;
};

struct UsbSessionStopResponsePacket {
    TransactionId tx_id;
    UsbSessionStopResponse payload;
};

struct GetMotorFeedbackResponsePacket {
    TransactionId tx_id;
    GetMotorFeedbackResponse payload;
};

struct StartMotionResponsePacket {
    TransactionId tx_id;
    StartMotionResponse payload;
};

struct StopMotionResponsePacket {
    TransactionId tx_id;
    StopMotionResponse payload;
};

struct SetJointImpedanceResponsePacket {
    TransactionId tx_id;
    SetJointImpedanceResponse payload;
};

struct SetCartesianImpedanceResponsePacket {
    TransactionId tx_id;
    SetCartesianImpedanceResponse payload;
};

struct SetEEFrameResponsePacket {
    TransactionId tx_id;
    SetEEFrameResponse payload;
};

struct SetLoadResponsePacket {
    TransactionId tx_id;
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
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::MotorFeedbackArray>
    : PacketTraitsBase<PacketTraits<fci::arm::MotorFeedbackArray>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::MotorFeedbackArray);
    static constexpr std::size_t size = sizeof(fci::arm::MotorFeedbackArray);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::GripperStatus>
    : PacketTraitsBase<PacketTraits<fci::arm::GripperStatus>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GripperStatus);
    static constexpr std::size_t size = sizeof(fci::arm::GripperStatus);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::AckPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::AckPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::Ack);
    static constexpr std::size_t size = sizeof(fci::arm::AckPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Ack;
};

template <>
struct PacketTraits<fci::arm::SetMotorStateRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetMotorStateRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetMotorStateRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetMotorStateRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetMotorStateResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetMotorStateResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetMotorStateResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetMotorStateResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::SetMotorControlModeRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetMotorControlModeRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetMotorControlModeRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetMotorControlModeRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetMotorControlModeResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetMotorControlModeResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetMotorControlModeResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetMotorControlModeResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::SetZeroRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetZeroRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetZeroRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetZeroRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetZeroResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetZeroResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetZeroResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetZeroResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::ClearErrorRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::ClearErrorRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::ClearErrorRequest);
    static constexpr std::size_t size = sizeof(fci::arm::ClearErrorRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::ClearErrorResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::ClearErrorResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::ClearErrorResponse);
    static constexpr std::size_t size = sizeof(fci::arm::ClearErrorResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::HomeAllRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::HomeAllRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::HomeAllRequest);
    static constexpr std::size_t size = sizeof(fci::arm::HomeAllRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::HomeAllResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::HomeAllResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::HomeAllResponse);
    static constexpr std::size_t size = sizeof(fci::arm::HomeAllResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::ClearFaultsRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::ClearFaultsRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::ClearFaultsRequest);
    static constexpr std::size_t size = sizeof(fci::arm::ClearFaultsRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::ClearFaultsResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::ClearFaultsResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::ClearFaultsResponse);
    static constexpr std::size_t size = sizeof(fci::arm::ClearFaultsResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::SdkClientConnectedRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SdkClientConnectedRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SdkClientConnectedRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SdkClientConnectedRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SdkClientConnectedResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SdkClientConnectedResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SdkClientConnectedResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SdkClientConnectedResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::SdkClientDisconnectedRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SdkClientDisconnectedRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SdkClientDisconnectedRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SdkClientDisconnectedRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SdkClientDisconnectedResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SdkClientDisconnectedResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SdkClientDisconnectedResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SdkClientDisconnectedResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::HomeDoneRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::HomeDoneRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::HomeDoneRequest);
    static constexpr std::size_t size = sizeof(fci::arm::HomeDoneRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::HomeDoneResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::HomeDoneResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::HomeDoneResponse);
    static constexpr std::size_t size = sizeof(fci::arm::HomeDoneResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::UsbSessionStartRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::UsbSessionStartRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::UsbSessionStartRequest);
    static constexpr std::size_t size = sizeof(fci::arm::UsbSessionStartRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::UsbSessionStartResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::UsbSessionStartResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::UsbSessionStartResponse);
    static constexpr std::size_t size = sizeof(fci::arm::UsbSessionStartResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::UsbSessionStopRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::UsbSessionStopRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::UsbSessionStopRequest);
    static constexpr std::size_t size = sizeof(fci::arm::UsbSessionStopRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::UsbSessionStopResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::UsbSessionStopResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::UsbSessionStopResponse);
    static constexpr std::size_t size = sizeof(fci::arm::UsbSessionStopResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::GetMotorFeedbackRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GetMotorFeedbackRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GetMotorFeedbackRequest);
    static constexpr std::size_t size = sizeof(fci::arm::GetMotorFeedbackRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::GetMotorFeedbackResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GetMotorFeedbackResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GetMotorFeedbackResponse);
    static constexpr std::size_t size = sizeof(fci::arm::GetMotorFeedbackResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::JointMITCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::JointMITCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::JointMITCommand);
    static constexpr std::size_t size = sizeof(fci::arm::JointMITCommandPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::EmergencyStopPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::EmergencyStopPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::EmergencyStop);
    static constexpr std::size_t size = sizeof(fci::arm::EmergencyStopPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::GripperCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GripperCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GripperCommand);
    static constexpr std::size_t size = sizeof(fci::arm::GripperCommandPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::JointPosVelCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::JointPosVelCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::JointPosVelCommand);
    static constexpr std::size_t size = sizeof(fci::arm::JointPosVelCommandPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::JointVelCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::JointVelCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::JointVelCommand);
    static constexpr std::size_t size = sizeof(fci::arm::JointVelCommandPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::JointPVTCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::JointPVTCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::JointPVTCommand);
    static constexpr std::size_t size = sizeof(fci::arm::JointPVTCommandPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::GetDeviceInfoRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GetDeviceInfoRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GetDeviceInfoRequest);
    static constexpr std::size_t size = sizeof(fci::arm::GetDeviceInfoRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::GetDeviceInfoResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::GetDeviceInfoResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::GetDeviceInfoResponse);
    static constexpr std::size_t size = sizeof(fci::arm::GetDeviceInfoResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::SetDeviceInfoRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetDeviceInfoRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetDeviceInfoRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetDeviceInfoRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetDeviceInfoResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetDeviceInfoResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetDeviceInfoResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetDeviceInfoResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

// ── New: StartMotion / StopMotion ──

template <>
struct PacketTraits<fci::arm::StartMotionRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::StartMotionRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::StartMotionRequest);
    static constexpr std::size_t size = sizeof(fci::arm::StartMotionRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::StartMotionResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::StartMotionResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::StartMotionResponse);
    static constexpr std::size_t size = sizeof(fci::arm::StartMotionResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::StopMotionRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::StopMotionRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::StopMotionRequest);
    static constexpr std::size_t size = sizeof(fci::arm::StopMotionRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::StopMotionResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::StopMotionResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::StopMotionResponse);
    static constexpr std::size_t size = sizeof(fci::arm::StopMotionResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

// ── New: SetJointImpedance / SetCartesianImpedance / SetEEFrame / SetLoad ──

template <>
struct PacketTraits<fci::arm::SetJointImpedanceRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetJointImpedanceRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetJointImpedanceRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetJointImpedanceRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetJointImpedanceResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetJointImpedanceResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetJointImpedanceResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetJointImpedanceResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::SetCartesianImpedanceRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetCartesianImpedanceRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetCartesianImpedanceRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetCartesianImpedanceRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetCartesianImpedanceResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetCartesianImpedanceResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetCartesianImpedanceResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetCartesianImpedanceResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::SetEEFrameRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetEEFrameRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetEEFrameRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetEEFrameRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetEEFrameResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetEEFrameResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetEEFrameResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetEEFrameResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::SetLoadRequestPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetLoadRequestPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetLoadRequest);
    static constexpr std::size_t size = sizeof(fci::arm::SetLoadRequestPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBRequestProto;
    static constexpr PacketCategory category = PacketCategory::Request;
};

template <>
struct PacketTraits<fci::arm::SetLoadResponsePacket>
    : PacketTraitsBase<PacketTraits<fci::arm::SetLoadResponsePacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::SetLoadResponse);
    static constexpr std::size_t size = sizeof(fci::arm::SetLoadResponsePacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

// ── New: CartesianPoseCommand / CartesianVelocityCommand ──

template <>
struct PacketTraits<fci::arm::CartesianPoseCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::CartesianPoseCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::CartesianPoseCommand);
    static constexpr std::size_t size = sizeof(fci::arm::CartesianPoseCommandPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

template <>
struct PacketTraits<fci::arm::CartesianVelocityCommandPacket>
    : PacketTraitsBase<PacketTraits<fci::arm::CartesianVelocityCommandPacket>> {
    static constexpr std::uint16_t cmd = fci::arm::to_u16(fci::arm::Command::CartesianVelocityCommand);
    static constexpr std::size_t size = sizeof(fci::arm::CartesianVelocityCommandPacket);
    static constexpr bool skip_memory_pool = true;
    using Protocol = USBBaseProto;
    static constexpr PacketCategory category = PacketCategory::Notification;
};

} // namespace RPL::Meta

#pragma pack(pop)

#endif // FCI_PROTOCOL_ARM_PACKETS_HPP
