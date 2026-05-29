// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#![no_std]

use core::panic::PanicInfo;
pub mod arch;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}