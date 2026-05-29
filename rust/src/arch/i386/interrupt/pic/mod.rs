// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
use core::arch::asm;
use crate::debug;
pub struct Pic;

const PIC1_COMMAND: u16 = 0x20;
const PIC1_DATA: u16 = 0x21;
const PIC2_COMMAND: u16 = 0xA0;
const PIC2_DATA: u16 = 0xA1;
const ICW1_INIT: u8 = 0x10;
const ICW1_ICW4: u8 = 0x01;
const ICW4_8086: u8 = 0x01;

impl Pic {
    unsafe fn inb(port: u16) -> u8 {
        let result: u8;
        unsafe {
            asm!(
                "in al, dx",
                out("al") result,
                in("dx") port,
                options(nostack, preserves_flags)
            );
        }
        result
    }
    unsafe fn outb(port: u16, value: u8) {
        unsafe {
            asm!(
                "out dx, al",
                in("dx") port,
                in("al") value,
                options(nostack, preserves_flags)
            )
        }
    }

    pub fn remap(offset1: u8, offset2: u8) {
        unsafe {
            let mask1 = Self::inb(PIC1_DATA);
            let mask2 = Self::inb(PIC2_DATA);
            Self::outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
            Self::outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
            Self::outb(PIC1_DATA, offset1);
            Self::outb(PIC2_DATA, offset2);
            Self::outb(PIC1_DATA, 0x04);
            Self::outb(PIC2_DATA, 0x02);
            Self::outb(PIC1_DATA, ICW4_8086);
            Self::outb(PIC2_DATA, ICW4_8086);
            Self::outb(PIC1_DATA, mask1);
            Self::outb(PIC2_DATA, mask2);
            debug!("PIC: remapped to 0x{} (master) and 0x{} (slave)", offset1, offset2);
        }
    }
    pub fn mask_all() {
        unsafe {
            Self::outb(PIC1_DATA, 0xFF);
            Self::outb(PIC2_DATA, 0xFF);
        }
    }
    pub fn unmask_irq(irq: u8) {
        unsafe {
            if irq < 8 {
                let mask = Self::inb(PIC1_DATA);
                Self::outb(PIC1_DATA, mask & !(1 << irq));
            } else {
                let mask = Self::inb(PIC2_DATA);
                Self::outb(PIC2_DATA, mask & !(1 << (irq - 8)));
            }
        }
        debug!("PIC: unmasked IRQ{}", irq);
    }
    pub fn mask_irq(irq: u8) {
        unsafe {
            if irq < 8 {
                let mask = Self::inb(PIC1_DATA);
                Self::outb(PIC1_DATA, mask | (1 << irq));
            } else {
                let mask = Self::inb(PIC2_DATA);
                Self::outb(PIC2_DATA, mask | (1 << (irq - 8)));
            }
        }
        debug!("PIC: masked IRQ{}", irq);
    }
    pub fn send_eoi(irq: u8) {
        unsafe {
            if irq >= 8 {
                Self::outb(PIC2_COMMAND, 0x20);
            }
            Self::outb(PIC1_COMMAND, 0x20);
        }
    }
}