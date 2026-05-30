// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
mod asm;

use super::idt::Idt;
use crate::info;

unsafe extern "C" {
    static isr_entry_table: [u32; 32];
}

pub(crate) fn init(idt: &mut Idt) {
    for i in 0..32 {
        let handler = unsafe { isr_entry_table[i] };
        idt.set_gate(i as u8, handler, 0x08, 0x8E);
    }
    info!("ISR: hello world");
}
