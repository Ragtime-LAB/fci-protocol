add_subdirectory(3rdparty/rpl)
add_library(fci_usb_protocol INTERFACE)
target_link_libraries(fci_usb_protocol INTERFACE rpl)
target_include_directories(fci_usb_protocol INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
