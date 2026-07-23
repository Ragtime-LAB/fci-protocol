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
    fci::arm::ArmControlModeRequestPacket,
    fci::arm::ArmControlModeResponsePacket,
    fci::arm::GripperControlModeRequestPacket,
    fci::arm::GripperControlModeResponsePacket,
    fci::arm::SetZeroRequestPacket,
    fci::arm::SetZeroResponsePacket,
    fci::arm::ClearErrorRequestPacket,
    fci::arm::ClearErrorResponsePacket,
    fci::arm::HomeAllRequestPacket,
    fci::arm::ClearFaultsRequestPacket,
    fci::arm::ClearFaultsResponsePacket,
    fci::arm::SdkClientConnectedRequestPacket,
    fci::arm::SdkClientConnectedResponsePacket,
    fci::arm::SdkClientDisconnectedRequestPacket,
    fci::arm::SdkClientDisconnectedResponsePacket,
    fci::arm::GetMotorFeedbackRequestPacket,
    fci::arm::GetMotorFeedbackResponsePacket,
    fci::arm::GetDeviceInfoRequestPacket,
    fci::arm::GetDeviceInfoResponsePacket,
    fci::arm::SetDeviceInfoRequestPacket,
    fci::arm::SetDeviceInfoResponsePacket,
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
