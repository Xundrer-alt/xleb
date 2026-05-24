#include "basic_drivers/timer.h"
#include "bootpr/get.h"
#include "debug.h"
#include "interrupt/init.h"
#include "halt.h"
#include "memory/mm.h"
#include "task/scheduler.h"

void kmain() {
    interrupt_init();
    get_bootloader_protocol();
    mm_init();
    timer_init();
    scheduler_init();
    halt();
}
