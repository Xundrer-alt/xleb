#include "bootpr/get.h"
#include "debug.h"
#include "interrupt/init.h"
#include "halt.h"

void kmain() {
    interrupt_init();
    get_bootloader_protocol();
    halt();
}
