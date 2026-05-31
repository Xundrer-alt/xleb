// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "debug.h"
#include "halt.h"
#include "mm/page_fault.h"
#include "test.h"

void page_fault_handler(regs_t *r) {
    DEBUG("Page Fault. Error code: 0x%x", r->err_code);
    DEBUG("EAX: 0x%x, EBX: 0x%x, ECX: 0x%x, EDX: 0x%x", r->eax, r->ebx, r->ecx, r->edx);
    DEBUG("EIP: 0x%x, CS: 0x%x, EFLAGS: 0x%x", r->eip, r->cs, r->eflags);
    halt();
}