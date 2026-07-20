#ifndef FLORID_USB_PROTOCOL_SESSION_UPGRADE_CONTROL_SESSION_HPP
#define FLORID_USB_PROTOCOL_SESSION_UPGRADE_CONTROL_SESSION_HPP

#include "florid_usb_protocol/message/upgrade.hpp"
#include "florid_usb_protocol/session/stream_session.hpp"
#include "florid_usb_protocol/transport/byte_stream_transport.hpp"

namespace florid::usb::session {

template <typename TickProvider, typename SendTransport>
using UpgradeControlSession = StreamSession<
    TickProvider,
    SendTransport,
    florid::usb::upgrade::GetBootStatusRequest,
    florid::usb::upgrade::BootStatusResponse,
    florid::usb::upgrade::StartUpgradeRequest,
    florid::usb::upgrade::StartUpgradeResponse,
    florid::usb::upgrade::RebootRequest,
    florid::usb::upgrade::RebootingResponse>;

template <typename TickProvider>
using UpgradeControlCallbackSession =
    UpgradeControlSession<TickProvider, florid::usb::transport::FunctionPointerByteStreamTransport>;

} // namespace florid::usb::session

#endif // FLORID_USB_PROTOCOL_SESSION_UPGRADE_CONTROL_SESSION_HPP
