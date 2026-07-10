#ifndef FLORID_USB_PROTOCOL_UPGRADE_TRANSPORT_HPP
#define FLORID_USB_PROTOCOL_UPGRADE_TRANSPORT_HPP

#include "florid_usb_protocol/upgrade/packets.hpp"
#include "RPL/USBTransport.hpp"

namespace florid::usb::upgrade {

template <typename TickProvider>
using Transport = RPL::USBTransportFn<
    RPL::AckManager<TickProvider>,
    USBAck,
    GetBootStatusRequest,
    BootStatusResponse,
    StartUpgradeRequest,
    StartUpgradeResponse,
    WriteChunkRequest,
    ChunkWrittenResponse,
    FinishUpgradeRequest,
    FinishUpgradeResponse,
    AbortUpgradeRequest,
    UpgradeAbortedResponse,
    SetPendingRequest,
    PendingSetResponse,
    RebootRequest,
    RebootingResponse>;

} // namespace florid::usb::upgrade

#endif // FLORID_USB_PROTOCOL_UPGRADE_TRANSPORT_HPP
