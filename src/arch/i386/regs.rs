// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#[allow(dead_code)]
pub struct Regs {
    pub edi: u32,
    pub esi: u32,
    pub ebp: u32,
    pub esp: u32,
    pub ebx: u32,
    pub edx: u32,
    pub ecx: u32,
    pub eax: u32,
    pub gs: u32,
    pub fs: u32,
    pub es: u32,
    pub ds: u32,
    pub int_no: u32,
    pub err_code: u32,
    pub eip: u32,
    pub cs: u32,
    pub eflags: u32,
    pub user_esp: u32,
    pub user_ss: u32,
}

impl Regs {
    pub const fn empty() -> Self {
        Self {
            edi: 0, esi: 0, ebp: 0, esp: 0,
            ebx: 0, edx: 0, ecx: 0, eax: 0,
            gs: 0, fs: 0, es: 0, ds: 0,
            int_no: 0, err_code: 0,
            eip: 0, cs: 0, eflags: 0,
            user_esp: 0, user_ss: 0,
        }
    }
}