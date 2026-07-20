#ifndef FLORID_USB_PROTOCOL_SESSION_STREAM_SESSION_HPP
#define FLORID_USB_PROTOCOL_SESSION_STREAM_SESSION_HPP

#include "RPL/Packets/USBAck.hpp"
#include "RPL/USBTransport.hpp"

namespace florid::usb::session {

template <typename TickProvider, typename SendTransport, typename... Packets>
using StreamSession = RPL::USBTransport<
    RPL::AckManager<TickProvider>,
    SendTransport,
    USBAck,
    Packets...>;

} // namespace florid::usb::session

#endif // FLORID_USB_PROTOCOL_SESSION_STREAM_SESSION_HPP
