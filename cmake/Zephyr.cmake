if(NOT CONFIG_FCI_PROTOCOL)
    return()
endif()

zephyr_library_named(fci_protocol)

zephyr_include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_CURRENT_LIST_DIR}/../3rdparty/rpl/include
)

target_compile_features(fci_protocol PUBLIC cxx_std_20)
target_compile_definitions(fci_protocol PUBLIC FRAME_HEADER_TAG=0xA5)
