#include "interrupt/init.h"
#include "debug.h"
#include "halt.h"

void kmain() {
    interrupt_init();
    halt();
}
