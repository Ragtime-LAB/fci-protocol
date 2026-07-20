if(ZEPHYR_BASE)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/Zephyr.cmake)
else()
    add_subdirectory(3rdparty/rpl)

    add_library(fci_usb_protocol INTERFACE)
    add_library(florid_usb_protocol ALIAS fci_usb_protocol)

    target_link_libraries(fci_usb_protocol INTERFACE rpl)
    target_include_directories(fci_usb_protocol INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_compile_features(fci_usb_protocol INTERFACE cxx_std_20)
endif()
