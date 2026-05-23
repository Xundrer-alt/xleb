set(SRC
    idt.c
    intentry.S
    irq.c
    isr.c
    pic.c
)
target_sources(kernel PRIVATE ${SRC})
