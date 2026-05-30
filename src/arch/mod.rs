// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
pub trait Arch {
    fn halt() -> !;
    fn interrupt_init();
}

#[cfg(target_arch = "x86")]
pub mod i386;
#[cfg(target_arch = "x86")]
pub use i386::I386Arch as CurrentArch;

#[unsafe(no_mangle)]
pub extern "C" fn halt() -> ! {
    CurrentArch::halt()
}

#[unsafe(no_mangle)]
pub extern "C" fn interrupt_init() {
    CurrentArch::interrupt_init()
}