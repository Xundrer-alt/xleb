set(SRC
    lmem.c
    map.c
    unmap.c
    vmalloc.c
    vpage.c
)
target_sources(kernel PRIVATE ${SRC})