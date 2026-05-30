// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
use core::arch::global_asm;

global_asm!(
    r#"
.section .data
.align 8
gdt:
    .long 0x00000000
    .long 0x00000000
    .long 0x0000FFFF
    .long 0x00CF9A00
    .long 0x0000FFFF
    .long 0x00CF9200
    .long 0x0000FFFF
    .long 0x00CFFA00
    .long 0x0000FFFF
    .long 0x00CFF200
    .space 8
gdt_end:

gdt_ptr:
    .word gdt_end - gdt - 1
    .long gdt

.section .text
.global gdt_load
gdt_load:
    lgdt [gdt_ptr]
    push 0x08
    lea eax, [reload_cs]
    push eax
    retf

reload_cs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
"#
);

unsafe extern "C" {
    pub fn gdt_load();
}