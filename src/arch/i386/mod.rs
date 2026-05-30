// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
use super::Arch;
use core::arch::asm;

mod boot;
pub(crate) mod debug;
pub(crate) mod interrupt;
mod regs;
mod timer;

pub(crate) struct I386Arch;
impl Arch for I386Arch {
    fn halt() -> ! {
        unsafe {
            loop {
                asm!("hlt", options(nomem, nostack, preserves_flags));
            }
        }
    }
    fn init() {
        interrupt::init();
        timer::init();
    }
}
