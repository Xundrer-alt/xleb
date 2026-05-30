// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
pub(crate) trait Arch {
    fn halt() -> !;
    fn interrupt_init();
}

#[cfg(target_arch = "x86")]
pub(crate) mod i386;
#[cfg(target_arch = "x86")]
pub(crate) use i386::I386Arch as CurrentArch;