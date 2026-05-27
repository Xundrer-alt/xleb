set(SRC
    cmdline.c
    data_parser.c
    header.S
    mmap.c
    modules.c
)
target_sources(kernel PRIVATE ${SRC})
