// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
mod entry;
mod gdt;
mod multiboot1;

unsafe extern "C" {
    static boot_magic: u32;
}

pub(crate) fn init() {
    unsafe {
        if boot_magic == 0x2BADB002 {
            multiboot1::parse_data();
        } else {
            panic!("Unknown boot protocol");
        }
    }
}