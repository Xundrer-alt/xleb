#include "interrupt/init.h"
#include "debug.h"

void kmain() {
    interrupt_init();
    __asm__ volatile ("int $0x00"); // ISR test
}
