#include "boot/multiboot1/info.h"
#include "boot/multiboot1/mod.h"
#include "debug.h"
#include "mm/virtconv.h"

void process_modules(multiboot_info_t *mbi) {
    if (!(mbi->flags & MULTIBOOT_INFO_MODS)) return;
    INFO("- modules (%u):", mbi->mods_count);
    multiboot_module_t *mods = (multiboot_module_t *)PHYS_TO_VIRT(mbi->mods_addr);
    for (uint32_t i = 0; i < mbi->mods_count; i++) {
        INFO("  - module %u:\n", i);
        INFO("    - address: 0x%x - 0x%x\n", mods[i].mod_start, mods[i].mod_end);
        INFO("    - size: %u bytes\n", mods[i].mod_end - mods[i].mod_start);
        if (mods[i].cmdline) {
            INFO("    - cmdline: %s\n", (char *)mods[i].cmdline);
        }
    }
}