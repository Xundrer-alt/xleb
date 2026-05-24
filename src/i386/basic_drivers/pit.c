#include "debug.h"
#include "interrupt/irq.h"
#include "basic_drivers/timer.h"
#include "iob.h"

#define TIMER_HZ 100
static volatile uint32_t timer_ticks = 0;

static void timer_handler(regs_t *r) {
    timer_ticks++;
}

void timer_init() {
    uint32_t divisor = 1193180 / TIMER_HZ;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
    irq_register_handler(0, timer_handler);
    INFO("PIT timer: hello world");
}

uint32_t timer_get_ticks() {
    return timer_ticks;
}