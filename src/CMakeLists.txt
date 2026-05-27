if(NOT ENABLE_TESTS)
    set(SRC
        kmain.c
    )
endif()
target_sources(kernel PRIVATE ${SRC})
add_subdirectory(${ARCH})
