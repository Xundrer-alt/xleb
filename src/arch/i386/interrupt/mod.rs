// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
use self::idt::Idt;
use core::arch::asm;

mod idt;
mod irq;
mod isr;
mod pic;

pub(crate) fn init() {
    let mut idt = Idt::new();
    isr::init(&mut idt);
    irq::init(&mut idt);
    idt::init(&idt);
    // TEST: int 0x0
    unsafe {
        asm!("xor eax, eax", "div eax");
    }
}
