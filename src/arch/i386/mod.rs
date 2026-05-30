// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
use super::Arch;
use core::arch::asm;

mod boot;
pub(crate) mod debug;
mod interrupt;
mod regs;

pub(crate) struct I386Arch;
impl Arch for I386Arch {
    fn halt() -> ! {
        unsafe {
            loop {
                asm!("hlt", options(nomem, nostack, preserves_flags));
            }
        }
    }
    fn interrupt_init() {
        interrupt::init();
    }
}
