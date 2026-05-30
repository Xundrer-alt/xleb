// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
mod asm;

use super::idt::Idt;
use super::pic;
use crate::info;

unsafe extern "C" {
    static irq_entry_table: [u32; 16];
}

pub(crate) fn init(idt: &mut Idt) {
    for i in 0..16 {
        let handler = unsafe { irq_entry_table[i] };
        idt.set_gate(32 + i as u8, handler, 0x08, 0x8E);
    }
    pic::remap(32, 40);
    pic::mask_all();
    info!("IRQ: hello world");
}
