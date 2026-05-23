#include "debug.h"
#include "interrupt/idt.h"
#include "interrupt/init.h"
#include "interrupt/pic.h"

static struct idt_entry idt[IDT_SIZE];
static struct idt_ptr ptr;
extern uint32_t isr_entry_table[32];
extern uint32_t irq_entry_table[16];

void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t type_attr) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].type_attr = type_attr;
}

void interrupt_init() {
    for (int i = 0; i < 32; i++) {
        idt_set_gate(i, isr_entry_table[i], 0x08, 0x8E);
    }
    DEBUG("ISR: hello world");
    for (int i = 0; i < 16; i++) {
        idt_set_gate(32 + i, irq_entry_table[i], 0x08, 0x8E);
    }
    pic_remap(32, 40);
    pic_mask_all();
    DEBUG("IRQ: hello world");
    ptr.limit = sizeof(idt) - 1;
    ptr.base = (uint32_t)idt;
    __asm__ volatile("lidt %0" : : "m"(ptr));
    INFO("IDT: hello world");
}
