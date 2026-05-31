set(SRC
    lmem.c
    map.c
    vmalloc.c
    vpage_alloc.c
)
target_sources(kernel PRIVATE ${SRC})