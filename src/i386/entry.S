.section .text
.global _entry
_entry:
    cli
    movl $stack_top, %esp
    movl %eax, (boot_magic)
    movl %ebx, (info_ptr)
    call gdt_load
    call get_bootloader_protocol
    call kmain
    hlt

.section .data

.global boot_magic
boot_magic:
    .long 0

.global info_ptr
info_ptr:
    .long 0

.section .bss
stack_top:
    .skip 16384
stack_bottom: