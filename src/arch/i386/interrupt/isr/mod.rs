// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
mod asm;

use super::idt::Idt;
use crate::{debug,info,error};
use crate::arch::i386::regs::Regs;

unsafe extern "C" {
    static isr_entry_table: [u32; 32];
}

const EX_NAMES: [&str; 32] = [
    "Division by Zero",
    "Debug",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 FPU Error",
    "Alignment Check",
    "Machine Check",
    "SIMD Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved",
];

#[unsafe(no_mangle)]
pub(crate) extern "C" fn isr_handler(regs: &mut Regs) {
    let int_no = regs.int_no as usize;
    if int_no == 1 || int_no == 3 {
        debug!("Debug exception {}: {}", int_no, EX_NAMES[int_no]);
        debug!(
            "EAX: 0x{:x}, EBX: 0x{:x}, ECX: 0x{:x}, EDX: 0x{:x}",
            regs.eax, regs.ebx, regs.ecx, regs.edx
        );
        debug!(
            "EIP: 0x{:x}, CS: 0x{:x}, EFLAGS: 0x{:x}",
            regs.eip, regs.cs, regs.eflags
        );
        return;
    }
    error!(
        "Fatal exception {}: {}. Error code: 0x{:x}",
        int_no, EX_NAMES[int_no], regs.err_code
    );
    error!(
        "EAX: 0x{:x}, EBX: 0x{:x}, ECX: 0x{:x}, EDX: 0x{:x}",
        regs.eax, regs.ebx, regs.ecx, regs.edx
    );
    error!(
        "EIP: 0x{:x}, CS: 0x{:x}, EFLAGS: 0x{:x}",
        regs.eip, regs.cs, regs.eflags
    );
    panic!("Fatal exception (see above)");
}

pub(crate) fn init(idt: &mut Idt) {
    for i in 0..32 {
        let handler = unsafe { isr_entry_table[i] };
        idt.set_gate(i as u8, handler, 0x08, 0x8E);
    }
    info!("ISR: hello world");
}
