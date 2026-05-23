set(SRC
    debug.c
    entry.S
)
target_include_directories(kernel PRIVATE
    include
)
target_sources(kernel PRIVATE ${SRC})
add_subdirectory(interrupt)
add_subdirectory(multiboot1)