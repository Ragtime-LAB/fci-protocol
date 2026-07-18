# florid_usb_protocol

This repository holds the shared USB protocol definitions used by `Usb2Arm`.

Current scope:
- bootloader upgrade protocol on top of RPL USB framing
- packet definitions plus host/device shared upgrade image helpers
- platform-independent transport alias for `RPL::USBTransport`

Main header:

```cpp
#include <florid_usb_protocol/protocol.hpp>
```

Upgrade protocol notes:
- request packets use RPL request/ack semantics
- data-bearing responses are separate packets carrying the original `req_id`
- `WriteChunkRequest` currently uses a fixed 1024-byte payload ceiling
- `data_size` is the aligned flash-programming length for the current chunk
- `valid_size` is the logical image byte count inside that chunk; trailing bytes
  are `0xFF` padding when `valid_size < data_size`
- `FirmwareImage` / `ChunkPlan` / `UpgradePlan` are transport-agnostic helpers
  for image CRC calculation, aligned chunking, and request packet building
- USB send/receive, retries, session state machines, and bootloader flash logic
  still belong in product code rather than this shared protocol library

Zephyr module support:
- `zephyr/module.yml` exposes this repository as a standard Zephyr module
- `zephyr/Kconfig` gates the library behind `CONFIG_FLORID_USB_PROTOCOL`
- root `CMakeLists.txt` detects `ZEPHYR_BASE` and dispatches to
  `cmake/Zephyr.cmake`; otherwise it behaves like a normal standalone CMake
  subproject

Recommended Zephyr integration boundary:
- this library owns packet definitions, RPL transport types, image/chunk
  helpers, and request/response builders
- the Zephyr app owns USB CDC I/O, protocol mode switching, upgrade policy,
  `UpgradeManager`, slot writes, and reboot policy
- a thin adapter layer should decode protocol requests and forward only the
  product-level actions upward, typically:
  - fill/respond boot status
  - request enter-upgrade mode
  - request reboot
  - pump transport RX/TX bytes between CDC and the protocol transport
