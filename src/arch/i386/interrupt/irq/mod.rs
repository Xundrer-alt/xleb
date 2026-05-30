// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
mod asm;

use super::idt::Idt;
use super::pic;
use crate::{debug,info,warn,error};
use crate::arch::i386::regs::Regs;
pub type IrqHandler = extern "C" fn(regs: &mut Regs);
static mut IRQ_TABLE: [Option<IrqHandler>; 16] = [None; 16];

unsafe extern "C" {
    static irq_entry_table: [u32; 16];
}

#[unsafe(no_mangle)]
pub(crate) extern "C" fn irq_handler(regs: &mut Regs) {
    let irq = (regs.int_no - 32) as u8;
    unsafe {
        if let Some(handler) = IRQ_TABLE[irq as usize] {
            handler(regs);
        } else {
            debug!("IRQ{}: no handler", irq);
        }
    }
    pic::send_eoi(irq);
}

pub(crate) fn register_handler(irq: u8, handler: IrqHandler) {
    if irq >= 16 {
        error!("Invalid IRQ ({})", irq);
    }
    unsafe {
        if IRQ_TABLE[irq as usize].is_some() {
            warn!("Overriding IRQ{}", irq);
        }
        IRQ_TABLE[irq as usize] = Some(handler);
        pic::unmask_irq(irq);
        debug!("IRQ{} handler registered", irq);
    }
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
