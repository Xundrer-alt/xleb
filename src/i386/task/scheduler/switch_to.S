# SPDX-License-Identifier: GPL-2.0
# Copyright (c) 2026 Xundrer-alt
.global switch_to
switch_to:
    pushl %ebp
    pushl %ebx
    pushl %esi
    pushl %edi
    pushfl

    movl 24(%esp), %eax
    movl %esp, (%eax)
    
    movl 28(%esp), %esp

    popfl
    popl %edi
    popl %esi
    popl %ebx
    popl %ebp

    ret