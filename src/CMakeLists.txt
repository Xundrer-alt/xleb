set(SRC
    kmain.c
)
target_sources(kernel PRIVATE ${SRC})
add_subdirectory(${ARCH})
