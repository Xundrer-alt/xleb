.section .text
.global _entry
_entry:
    cli
    movl $stack_top, %esp
    call kmain
    hlt

.section .bss
stack_top:
    .skip 16384
stack_bottom:
