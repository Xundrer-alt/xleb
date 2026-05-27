set(SRC
    entry.S
    get_bootloader_protocol.c
)
target_sources(kernel PRIVATE ${SRC})
add_subdirectory(multiboot1)