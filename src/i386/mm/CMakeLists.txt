set(SRC
    lowlevel.c
    init.c
)
target_sources(kernel PRIVATE ${SRC})
add_subdirectory(kheap)
add_subdirectory(ppage)
add_subdirectory(vmm)