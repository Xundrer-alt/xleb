.global switch_to
switch_to:
    pushl %ebp
    pushl %ebx
    pushl %esi
    pushl %edi

    movl 20(%esp), %eax
    movl %esp, (%eax)

    movl 24(%esp), %esp

    popl %edi
    popl %esi
    popl %ebx
    popl %ebp

    ret