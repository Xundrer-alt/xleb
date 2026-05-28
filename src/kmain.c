// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "basic_drivers/timer/mod.h"
#include "debug.h"
#include "interrupt/init.h"
#include "halt.h"
#include "mm/mm.h"
#include "task/scheduler/mod.h"
extern void get_bootloader_protocol();

void kmain() {
    interrupt_init();
    get_bootloader_protocol();
    mm_init();
    timer_init();
    scheduler_init();
    halt();
}
