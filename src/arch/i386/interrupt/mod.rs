// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
use self::idt::Idt;

mod idt;
pub(crate) mod irq;
mod isr;
pub(crate) mod pic;

pub(crate) fn init() {
    let mut idt = Idt::new();
    isr::init(&mut idt);
    irq::init(&mut idt);
    idt::init(&idt);
}
