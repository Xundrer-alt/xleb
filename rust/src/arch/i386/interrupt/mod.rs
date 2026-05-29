// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
pub struct InterruptController;
use core::arch::asm;
use self::idt::{Idt,IdtPtr};
use self::pic::Pic;
pub mod idt;
pub mod irq;
pub mod isr;
pub mod pic;
impl InterruptController {
    pub fn init() {
        unsafe extern "C" {
            static isr_entry_table: [u32; 32];
            static irq_entry_table: [u32; 16];
        }
        let mut idt = Idt::new(); 
        for i in 0..32 {
            let handler = unsafe { isr_entry_table[i] };
            idt.set_gate(i as u8, handler, 0x08, 0x8E);
        }
        for i in 0..16 {
            let handler = unsafe { irq_entry_table[i] };
            idt.set_gate(32 + i as u8, handler, 0x08, 0x8E);
        }
        Pic::remap(32, 40);
        Pic::mask_all();
        unsafe {
            let ptr = IdtPtr {
                limit: (core::mem::size_of_val(&idt) - 1) as u16,
                base: idt.entries.as_ptr() as u32,
            };
            asm!("lidt [{}]", in(reg) &ptr, options(nostack, preserves_flags));
            asm!("sti", options(nomem, nostack, preserves_flags));
        }
    }
}