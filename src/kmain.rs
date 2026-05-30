// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#![no_std]
#![no_main]

use crate::arch::Arch;
use core::panic::PanicInfo;
mod arch;

#[unsafe(no_mangle)]
pub(crate) extern "C" fn kmain() -> ! {
    arch::CurrentArch::interrupt_init();
    arch::CurrentArch::halt()
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}
