#pragma once
#include "interrupt/idt.h"

typedef void (*irq_handler_t)(regs_t *regs);
void irq_register_handler(uint8_t irq, irq_handler_t handler);
void irq_unregister_handler(uint8_t irq);