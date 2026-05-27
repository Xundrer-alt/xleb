set(SRC
    mask_irq.c
    remap.c
    send_eoi.c
    unmask_irq.c
)
target_sources(kernel PRIVATE ${SRC})