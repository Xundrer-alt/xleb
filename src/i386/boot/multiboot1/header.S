.section .multiboot
.align 4
multiboot1_h_start:
    .long 0x1BADB002
    .long 0x00000003
    .long -(0x1BADB002 + 0x00000003)
multiboot1_h_end: