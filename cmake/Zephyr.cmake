if(NOT CONFIG_FLORID_USB_PROTOCOL)
    return()
endif()

zephyr_library_named(florid_usb_protocol)

zephyr_library_include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_CURRENT_LIST_DIR}/../3rdparty/rpl/include
)

target_compile_features(florid_usb_protocol PUBLIC cxx_std_20)
target_compile_definitions(florid_usb_protocol PUBLIC FRAME_HEADER_TAG=0xA5)
