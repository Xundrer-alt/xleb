#include "bootpr/multiboot1.h"
#include "debug.h"
#include "halt.h"
#include "mm.h"
extern uint32_t info_ptr;

static void process_cmdline(const char *cmdline) {
    if (!cmdline) return;
    INFO("- cmdline: %s", cmdline);
}

static void process_memory_map(multiboot_info_t *mbi) {
    if (!(mbi->flags & MULTIBOOT_INFO_MEM_MAP)) return;
    INFO("- memory map (%u bytes):", mbi->mmap_length);
    multiboot_memory_map_t *mmap = (multiboot_memory_map_t *)mbi->mmap_addr;
    uint32_t mmap_end = mbi->mmap_addr + mbi->mmap_length;
    
    while ((uint32_t)mmap < mmap_end) {
        uint32_t start = (uint32_t)mmap->addr;
        uint32_t end = (uint32_t)(mmap->addr + mmap->len - 1);
        uint32_t size = (uint32_t)mmap->len;
        const char *type_str = "unknown";
        switch (mmap->type) {
            case MULTIBOOT_MEMORY_AVAILABLE:
                type_str = "available";
                break;
            case MULTIBOOT_MEMORY_RESERVED:
                type_str = "reserved";
                break;
            case MULTIBOOT_MEMORY_ACPI_RECLAIMABLE:
                type_str = "ACPI reclaim";
                break;
            case MULTIBOOT_MEMORY_NVS:
                type_str = "ACPI NVS";
                break;
            case MULTIBOOT_MEMORY_BADRAM:
                type_str = "bad RAM";
                break;
            default:
                type_str = "reserved";
                break;
        }
        INFO("  - [0x%x - 0x%x] %s (%u KB)",
            start, end, type_str, size / 1024);
        mmap = (multiboot_memory_map_t *)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
    }
}

static void process_modules(multiboot_info_t *mbi) {
    if (!(mbi->flags & MULTIBOOT_INFO_MODS)) return;
    INFO("- modules (%u):", mbi->mods_count);
    multiboot_module_t *mods = (multiboot_module_t *)mbi->mods_addr;
    for (uint32_t i = 0; i < mbi->mods_count; i++) {
        INFO("  - module %u:\n", i);
        INFO("    - address: 0x%x - 0x%x\n", mods[i].mod_start, mods[i].mod_end);
        INFO("    - size: %u bytes\n", mods[i].mod_end - mods[i].mod_start);
        if (mods[i].cmdline) {
            INFO("    - cmdline: %s\n", (char *)mods[i].cmdline);
        }
    }
}

void multiboot1_parse_data() {
    if (!info_ptr) {
        ERROR("boot protocol seems to be multiboot1, but info_ptr = 0");
        halt();
    }
    multiboot_info_t *mbi = (multiboot_info_t *)info_ptr;
    INFO("boot protocol is multiboot1");
    DEBUG("multiboot info structure at 0x%x", info_ptr);
    INFO("START MULTIBOOT1 INFO PARSING");
    if (mbi->flags & MULTIBOOT_INFO_MEMORY) {
        INFO("- memory: lower=%u KB, upper=%u KB",
            mbi->mem_lower, mbi->mem_upper);
    }
    if (mbi->flags & MULTIBOOT_INFO_BOOTDEV) {
        INFO("- boot device: 0x%x", mbi->boot_device);
    }
    if (mbi->flags & MULTIBOOT_INFO_CMDLINE && mbi->cmdline) {
        process_cmdline((char *)mbi->cmdline);
    }
    process_memory_map(mbi);
    process_modules(mbi);
    INFO("END MULTIBOOT1 INFO PARSING");
}