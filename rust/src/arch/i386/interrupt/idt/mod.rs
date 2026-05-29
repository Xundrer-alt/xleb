// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
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
    pub entries: [IdtEntry; 256],
}

#[repr(C, packed)]
#[derive(Debug, Clone, Copy)]
pub struct IdtPtr {
    pub limit: u16,
    pub base: u32,
}

#[repr(C, packed)]
#[derive(Debug, Clone, Copy)]
pub struct Regs {
    pub edi: u32,
    pub esi: u32,
    pub ebp: u32,
    pub esp: u32,
    pub ebx: u32,
    pub edx: u32,
    pub ecx: u32,
    pub eax: u32,
    pub gs: u32,
    pub fs: u32,
    pub es: u32,
    pub ds: u32,
    pub int_no: u32,
    pub err_code: u32,
    pub eip: u32,
    pub cs: u32,
    pub eflags: u32,
    pub user_esp: u32,
    pub user_ss: u32,
}

impl IdtEntry {
    pub const fn empty() -> Self {
        Self {
            base_low: 0,
            selector: 0,
            zero: 0,
            type_attr: 0,
            base_high: 0,
        }
    }
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
    pub const fn empty() -> Self {
        Self {
            limit: 0,
            base: 0,
        }
    }
    pub fn from_idt(idt: &[IdtEntry; IDT_SIZE]) -> Self {
        Self {
            limit: (core::mem::size_of_val(idt) - 1) as u16,
            base: idt.as_ptr() as u32,
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

impl Regs {
    pub const fn empty() -> Self {
        Self {
            edi: 0, esi: 0, ebp: 0, esp: 0,
            ebx: 0, edx: 0, ecx: 0, eax: 0,
            gs: 0, fs: 0, es: 0, ds: 0,
            int_no: 0, err_code: 0,
            eip: 0, cs: 0, eflags: 0,
            user_esp: 0, user_ss: 0,
        }
    }
}