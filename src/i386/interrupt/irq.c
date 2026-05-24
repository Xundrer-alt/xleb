#include "debug.h"
#include "interrupt/idt.h"
#include "interrupt/irq.h"
#include "interrupt/pic.h"
#include "task/scheduler.h"

static irq_handler_t irq_table[16] = {0};

void irq_register_handler(uint8_t irq, irq_handler_t handler) {
    if (irq >= 16) {
        ERROR("IRQ: invalid IRQ number %d", irq);
        return;
    }
    if (irq_table[irq] != 0) {
        WARN("IRQ%d: overriding existing handler", irq);
    }
    irq_table[irq] = handler;
    pic_unmask_irq(irq);
    DEBUG("IRQ%d: handler registered", irq);

}

void irq_unregister_handler(uint8_t irq) {
    if (irq >= 16) {
        ERROR("IRQ: invalid IRQ number %d", irq);
        return;
    }

    irq_table[irq] = 0;
    pic_mask_irq(irq);
    DEBUG("IRQ%d: handler unregistered", irq);
}

void irq_handler(regs_t *regs) {
    uint8_t irq = regs->int_no - 32;
    pic_send_eoi(irq);
    if (irq >= 16) {
        ERROR("IRQ: invalid IRQ number %d (int_no=%d)", irq, regs->int_no);
        return;
    }
    if (irq_table[irq]) {
        irq_table[irq](regs);
    } else {
        DEBUG("IRQ%d: no handler", irq);
    }
    if (irq == 0) {
        schedule();
    }
}
