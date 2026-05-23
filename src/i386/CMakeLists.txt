set(SRC
    debug.c
    entry.S
    gdt.S
    get_bootloader_protocol.c
)
target_include_directories(kernel PRIVATE
    include
)
target_sources(kernel PRIVATE ${SRC})
add_subdirectory(interrupt)
add_subdirectory(mm)
add_subdirectory(multiboot1)