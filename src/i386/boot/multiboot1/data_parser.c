// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "boot/multiboot1/info.h"
#include "boot/multiboot1/mod.h"
#include "debug.h"
#include "rust_ffi.h"
#include "mm/virtconv.h"
#include "test.h"
extern uint32_t info_ptr;

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
    process_mmap(mbi);
    process_modules(mbi);
    INFO("END MULTIBOOT1 INFO PARSING");
}