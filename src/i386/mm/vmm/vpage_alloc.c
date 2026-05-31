// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "debug.h"
#include "mm/ppage/mod.h"
#include "mm/vmm/mod.h"
#include "mm/virtconv.h"
#include "stdint.h"

void* vpage_alloc(uint32_t *page_directory, uint32_t vaddr, uint32_t order, uint32_t flags) {
    if (!page_directory) {
        ERROR("vpage_alloc: page_directory is NULL");
        return NULL;
    }
    uint32_t paddr = (uint32_t)ppage_alloc(order, flags);
    if (!paddr) {
        ERROR("vpage_alloc: ppage_alloc failed for vaddr=0x%x", vaddr);
        return NULL;
    }
    vmm_map(page_directory, vaddr, paddr, PAGE_PRESENT | PAGE_WRITE);
    return (void*)vaddr;
}