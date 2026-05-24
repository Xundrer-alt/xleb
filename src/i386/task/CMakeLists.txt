set(SRC
    scheduler.c
    switch_to.S
    thread.c
)
target_sources(kernel PRIVATE ${SRC})