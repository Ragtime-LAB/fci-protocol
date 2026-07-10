# florid_usb_protocol

This repository holds the shared USB protocol definitions used by `Usb2Arm`.

Current scope:
- bootloader upgrade protocol on top of RPL USB framing
- packet definitions only
- platform-independent transport alias for `RPL::USBTransport`

Main header:

```cpp
#include <florid_usb_protocol/protocol.hpp>
```

Upgrade protocol notes:
- request packets use RPL request/ack semantics
- data-bearing responses are separate packets carrying the original `req_id`
- `WriteChunkRequest` currently uses a fixed 1024-byte payload ceiling
- `data_size` tells the receiver how many bytes inside the fixed chunk buffer
  are valid for the current transfer
