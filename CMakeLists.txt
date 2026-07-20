if(ZEPHYR_BASE)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/Zephyr.cmake)
else()
    add_subdirectory(3rdparty/rpl)

    add_library(fci_protocol INTERFACE)

    target_link_libraries(fci_protocol INTERFACE rpl)
    target_include_directories(fci_protocol INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_compile_features(fci_protocol INTERFACE cxx_std_20)
endif()
