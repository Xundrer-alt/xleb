// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#![no_std]
#![no_main]

use core::panic::PanicInfo;
use crate::arch::Arch;
pub mod arch;

#[unsafe(no_mangle)]
pub extern "C" fn kmain() -> ! {
    arch::CurrentArch::interrupt_init();
    arch::CurrentArch::halt()
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}