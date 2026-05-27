#include "boot/multiboot1/mod.h"
#include "debug.h"

void process_cmdline(const char *cmdline) {
    if (!cmdline) return;
    INFO("- cmdline: %s", cmdline);
}
