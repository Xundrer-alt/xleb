// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt

use core::arch::global_asm;

global_asm!(
    r#"
.section .multiboot
.align 4
multiboot1_h_start:
    .long 0x1BADB002
    .long 0x00000003
    .long -(0x1BADB002 + 0x00000003)
multiboot1_h_end:
"#, options(att_syntax));