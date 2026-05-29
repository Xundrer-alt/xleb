// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
use core::arch::asm;

const COM1_BASE: u16 = 0x3F8;
const LSR_REG: u16 = COM1_BASE + 5;
const THR_REG: u16 = COM1_BASE;

unsafe fn is_transmitter_empty() -> bool {
    let lsr: u8;
    unsafe {
        asm!(
            "in al, dx",
            out("al") lsr,
            in("dx") LSR_REG,
            options(nostack, preserves_flags)
        );
    }
    (lsr & (1 << 5)) != 0
}

unsafe fn uart_write_byte(c: u8) {
    unsafe {
        while !is_transmitter_empty() {}
        asm!(
            "out dx, al",
            in("dx") THR_REG,
            in("al") c,
            options(nostack, preserves_flags)
        );
    }
}

#[unsafe(no_mangle)]
pub extern "C" fn uart_putc(c: u8) {
    unsafe {
        if c == b'\n' {
            uart_write_byte(b'\r');
        }
        uart_write_byte(c);
    }
}
#[unsafe(no_mangle)]
pub extern "C" fn uart_puts(s: *const u8) {
    let mut i = 0;
    unsafe {
        while *s.add(i) != 0 {
            uart_putc(*s.add(i));
            i += 1;
        }
    }
}