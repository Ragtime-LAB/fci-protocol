add_subdirectory(3rdparty/rpl)

add_library(fci_usb_protocol
    src/upgrade/builder.cpp
    src/upgrade/chunk_plan.cpp
    src/upgrade/crc.cpp
    src/upgrade/image.cpp
)
add_library(florid_usb_protocol ALIAS fci_usb_protocol)

target_link_libraries(fci_usb_protocol PUBLIC rpl)
target_include_directories(fci_usb_protocol PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(fci_usb_protocol PUBLIC cxx_std_20)
