#include "bootpr/multiboot1.h"
#include "debug.h"
#include "halt.h"
#include "mm/lowlevel.h"
#include "mm/mm.h"
extern uint32_t info_ptr;

extern uint32_t _kernel_start;
extern uint32_t _kernel_end;

static void process_cmdline(const char *cmdline) {
    if (!cmdline) return;
    INFO("- cmdline: %s", cmdline);
}

static void process_memory_map(multiboot_info_t *mbi) {
    if (!(mbi->flags & MULTIBOOT_INFO_MEM_MAP)) return;
    INFO("- memory map (%u bytes):", mbi->mmap_length);
    multiboot_memory_map_t *mmap = (multiboot_memory_map_t *)PHYS_TO_VIRT(mbi->mmap_addr);
    uint32_t mmap_end = PHYS_TO_VIRT(mbi->mmap_addr) + mbi->mmap_length;
    INFO("  - [0x%x - 0x%x] lowlevel (%u KB)",
            VIRT_TO_PHYS((uint32_t)&_kernel_end), LOWLEVEL_LIMIT - 1, ((uint32_t)LOWLEVEL_LIMIT - 1 - VIRT_TO_PHYS((uint32_t)&_kernel_end)) / 1024);
    while ((uint32_t)mmap < mmap_end && memory_map.region_count < MAX_MEMORY_REGIONS) {
        memory_region_t *region = &memory_map.regions[memory_map.region_count];
        region->start = (uint32_t)mmap->addr;
        region->end = (uint32_t)(mmap->addr + mmap->len - 1);
        region->size = (uint32_t)mmap->len;
        const char *type_str = "unknown";
        switch (mmap->type) {
            case MULTIBOOT_MEMORY_AVAILABLE:
                if (region->end > LOWLEVEL_LIMIT) {
                    region->start = (region->start > LOWLEVEL_LIMIT) ? region->start : LOWLEVEL_LIMIT;
                    region->size = region->end - region->start;
                    region->type = MEMORY_AVAILABLE;
                    memory_map.available_memory += region->size;
                    type_str = "available";
                } else {
                    region->type = MEMORY_RESERVED;
                    type_str = "reserved";
                }
                break;
            case MULTIBOOT_MEMORY_RESERVED:
                type_str = "reserved";
                region->type = MEMORY_RESERVED;
                break;
            case MULTIBOOT_MEMORY_ACPI_RECLAIMABLE:
                type_str = "ACPI reclaim";
                region->type = MEMORY_ACPI_RECLAIMABLE;
                break;
            case MULTIBOOT_MEMORY_NVS:
                type_str = "ACPI NVS";
                region->type = MEMORY_ACPI_NVS;
                break;
            case MULTIBOOT_MEMORY_BADRAM:
                type_str = "bad RAM";
                region->type = MEMORY_BADRAM;
                break;
            default:
                type_str = "reserved";
                region->type = MEMORY_RESERVED;
                break;
        }
        INFO("  - [0x%x - 0x%x] %s (%u KB)",
            region->start, region->end, type_str, region->size / 1024);
        memory_map.region_count++;
        mmap = (multiboot_memory_map_t *)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
    }
    INFO("- total available memory: %d MB", memory_map.available_memory / (1024 * 1024));
}

static void process_modules(multiboot_info_t *mbi) {
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

void multiboot1_parse_data() {
    if (!info_ptr) {
        ERROR("boot protocol seems to be multiboot1, but info_ptr = 0");
        halt();
    }
    multiboot_info_t *mbi = (multiboot_info_t *)PHYS_TO_VIRT(info_ptr);
    INFO("boot protocol is multiboot1");
    DEBUG("multiboot info structure at 0x%x", info_ptr);
    INFO("START MULTIBOOT1 INFO PARSING");
    if (mbi->flags & MULTIBOOT_INFO_BOOTDEV) {
        INFO("- boot device: 0x%x", mbi->boot_device);
    }
    if (mbi->flags & MULTIBOOT_INFO_CMDLINE && mbi->cmdline) {
        process_cmdline((char *)PHYS_TO_VIRT(mbi->cmdline));
    }
    process_memory_map(mbi);
    process_modules(mbi);
    INFO("END MULTIBOOT1 INFO PARSING");
}