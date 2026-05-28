// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#pragma once
#include "interrupt/idt/mod.h"

typedef void (*irq_handler_t)(regs_t *regs);
extern irq_handler_t irq_table[16];
void irq_register_handler(uint8_t irq, irq_handler_t handler);
void irq_unregister_handler(uint8_t irq);