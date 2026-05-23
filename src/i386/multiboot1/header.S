.section .multiboot
.align 4
multiboot1_h_start:
    .align 4
    .long 0x1BADB002
    .long 0x00
    .long -(0x1BADB002 + 0x00)
multiboot1_h_end: