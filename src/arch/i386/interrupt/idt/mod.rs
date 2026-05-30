// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
use crate::info;
use core::arch::asm;
pub const IDT_SIZE: usize = 256;

#[repr(C, packed)]
#[derive(Debug, Clone, Copy)]
pub struct IdtEntry {
    pub base_low: u16,
    pub selector: u16,
    pub zero: u8,
    pub type_attr: u8,
    pub base_high: u16,
}

#[repr(C, packed)]
#[derive(Debug, Clone, Copy)]
pub struct Idt {
    pub entries: [IdtEntry; IDT_SIZE],
}

#[repr(C, packed)]
#[derive(Debug, Clone, Copy)]
pub struct IdtPtr {
    pub limit: u16,
    pub base: u32,
}

impl IdtEntry {
    pub const fn new(base: u32, selector: u16, type_attr: u8) -> Self {
        Self {
            base_low: (base & 0xFFFF) as u16,
            base_high: ((base >> 16) & 0xFFFF) as u16,
            selector,
            zero: 0,
            type_attr,
        }
    }
}

impl IdtPtr {
    pub fn from_idt(idt: &Idt) -> Self {
        Self {
            limit: (core::mem::size_of_val(idt) - 1) as u16,
            base: idt.entries.as_ptr() as u32,
        }
    }
    pub unsafe fn load(&self) {
        unsafe { asm!("lidt [{}]", in(reg) self, options(nostack, preserves_flags)) }
    }
}

impl Idt {
    pub const fn new() -> Self {
        Self {
            entries: [IdtEntry::new(0, 0, 0); 256],
        }
    }
    pub fn set_gate(&mut self, num: u8, base: u32, selector: u16, type_attr: u8) {
        if let Some(entry) = self.entries.get_mut(num as usize) {
            *entry = IdtEntry::new(base, selector, type_attr);
        }
    }
}

pub(crate) fn init(idt: &Idt) {
    unsafe {
        let ptr = IdtPtr::from_idt(idt);
        ptr.load();
        asm!("sti", options(nomem, nostack, preserves_flags));
    }
    info!("IDT: hello world");
}
