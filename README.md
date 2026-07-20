# florid_usb_protocol

This repository holds the shared USB protocol definitions used by `Usb2Arm`.

Current scope:
- bootloader control protocol on top of RPL USB framing
- packet definitions and shared transport alias
- platform-independent transport alias for `RPL::USBTransport`

Main header:

```cpp
#include <florid_usb_protocol/protocol.hpp>
```

Upgrade protocol notes:
- request packets use RPL request/ack semantics
- data-bearing responses are separate packets carrying the original `req_id`
- this tree now only carries boot status, upgrade-mode switch, and reboot
  control packets; image upload is handled elsewhere

Zephyr module support:
- `zephyr/module.yml` exposes this repository as a standard Zephyr module
- `zephyr/Kconfig` gates the library behind `CONFIG_FLORID_USB_PROTOCOL`
- root `CMakeLists.txt` detects `ZEPHYR_BASE` and dispatches to
  `cmake/Zephyr.cmake`; otherwise it behaves like a normal standalone CMake
  subproject

Recommended Zephyr integration boundary:
- this library owns packet definitions and RPL transport types
- the Zephyr app owns USB CDC I/O, protocol mode switching, upgrade policy,
  `UpgradeManager`, slot writes, and reboot policy
- a thin adapter layer should decode protocol requests and forward only the
  product-level actions upward, typically:
  - fill/respond boot status
  - request enter-upgrade mode
  - request reboot
  - pump transport RX/TX bytes between CDC and the protocol transport
