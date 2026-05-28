set(SRC
    add_region.c
    alloc.c
    free.c
    init.c
)
target_sources(kernel PRIVATE ${SRC})