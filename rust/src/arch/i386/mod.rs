// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
use core::arch::asm;
use super::Arch;

pub mod interrupt;
pub mod debug;
pub use interrupt::InterruptController;

pub struct I386Arch;
impl Arch for I386Arch {
    fn halt() -> ! {
        unsafe {
            loop {
                asm!("hlt", options(nomem, nostack, preserves_flags));
            }
        }
    }
    fn interrupt_init() {
        InterruptController::init();
    }
}