set(SRC
    entry.S
    handler.c
    register.c
    unregister.c
)
target_sources(kernel PRIVATE ${SRC})