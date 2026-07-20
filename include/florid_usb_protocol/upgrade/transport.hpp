#ifndef FLORID_USB_PROTOCOL_UPGRADE_TRANSPORT_HPP
#define FLORID_USB_PROTOCOL_UPGRADE_TRANSPORT_HPP

#include "florid_usb_protocol/session/upgrade_control_session.hpp"

namespace florid::usb::upgrade {

template <typename TickProvider>
using Transport = florid::usb::session::UpgradeControlCallbackSession<TickProvider>;

} // namespace florid::usb::upgrade

#endif // FLORID_USB_PROTOCOL_UPGRADE_TRANSPORT_HPP
