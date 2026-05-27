set(SRC
    add_thread.c
    do.c
    init.c
    switch_to.S
)
target_sources(kernel PRIVATE ${SRC})