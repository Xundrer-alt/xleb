set(SRC
    init.c
    page_fault.c
)
target_sources(kernel PRIVATE ${SRC})
add_subdirectory(kheap)
add_subdirectory(ppage)
add_subdirectory(vmm)