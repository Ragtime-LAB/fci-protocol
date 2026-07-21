#ifndef FCI_PROTOCOL_SESSION_ARM_CONTROL_SESSION_HPP
#define FCI_PROTOCOL_SESSION_ARM_CONTROL_SESSION_HPP

#include "fci_protocol/message/arm.hpp"
#include "fci_protocol/session/stream_session.hpp"
#include "fci_protocol/transport/byte_stream_transport.hpp"

namespace fci::session {

template <typename TickProvider, typename SendTransport>
using ArmControlSession = StreamSession<
    TickProvider,
    SendTransport,
    fci::arm::ArmStatus,
    fci::arm::MotorFeedbackArray,
    fci::arm::GripperStatus,
    fci::arm::AckPacket,
    fci::arm::SetMotorStateRequestPacket,
    fci::arm::SetMotorStateResponsePacket,
    fci::arm::SetMotorControlModeRequestPacket,
    fci::arm::SetMotorControlModeResponsePacket,
    fci::arm::SetZeroRequestPacket,
    fci::arm::SetZeroResponsePacket,
    fci::arm::ClearErrorRequestPacket,
    fci::arm::ClearErrorResponsePacket,
    fci::arm::HomeAllRequestPacket,
    fci::arm::HomeAllResponsePacket,
    fci::arm::ClearFaultsRequestPacket,
    fci::arm::ClearFaultsResponsePacket,
    fci::arm::SdkClientConnectedRequestPacket,
    fci::arm::SdkClientConnectedResponsePacket,
    fci::arm::SdkClientDisconnectedRequestPacket,
    fci::arm::SdkClientDisconnectedResponsePacket,
    fci::arm::HomeDoneRequestPacket,
    fci::arm::HomeDoneResponsePacket,
    fci::arm::UsbSessionStartRequestPacket,
    fci::arm::UsbSessionStartResponsePacket,
    fci::arm::UsbSessionStopRequestPacket,
    fci::arm::UsbSessionStopResponsePacket,
    fci::arm::GetMotorFeedbackRequestPacket,
    fci::arm::GetMotorFeedbackResponsePacket,
    fci::arm::GetDeviceInfoRequestPacket,
    fci::arm::GetDeviceInfoResponsePacket,
    fci::arm::SetDeviceInfoRequestPacket,
    fci::arm::SetDeviceInfoResponsePacket,
    fci::arm::StartMotionRequestPacket,
    fci::arm::StartMotionResponsePacket,
    fci::arm::StopMotionRequestPacket,
    fci::arm::StopMotionResponsePacket,
    fci::arm::SetJointImpedanceRequestPacket,
    fci::arm::SetJointImpedanceResponsePacket,
    fci::arm::SetCartesianImpedanceRequestPacket,
    fci::arm::SetCartesianImpedanceResponsePacket,
    fci::arm::SetEEFrameRequestPacket,
    fci::arm::SetEEFrameResponsePacket,
    fci::arm::SetLoadRequestPacket,
    fci::arm::SetLoadResponsePacket,
    fci::arm::JointMITCommandPacket,
    fci::arm::EmergencyStopPacket,
    fci::arm::GripperCommandPacket,
    fci::arm::JointPosVelCommandPacket,
    fci::arm::JointVelCommandPacket,
    fci::arm::JointPVTCommandPacket,
    fci::arm::CartesianPoseCommandPacket,
    fci::arm::CartesianVelocityCommandPacket>;

template <typename TickProvider>
using ArmControlCallbackSession =
    ArmControlSession<TickProvider, fci::transport::FunctionPointerByteStreamTransport>;

} // namespace fci::session

#endif // FCI_PROTOCOL_SESSION_ARM_CONTROL_SESSION_HPP
