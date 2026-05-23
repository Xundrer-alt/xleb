.section .multiboot
multiboot_h_start:
    .align 4
    .long 0x1BADB002
    .long 0x00
    .long -(0x1BADB002 + 0x00)
multiboot_h_end:
