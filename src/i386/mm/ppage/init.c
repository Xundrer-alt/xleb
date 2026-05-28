// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "debug.h"
#include "list.h"
#include "mm/mm.h"
#include "mm/ppage/mod.h"
#include "stdint.h"

memory_map_t memory_map;
free_block_t *free_lists[MAX_ORDER + 1];

void ppage_init() {
    for (int i = 0; i < memory_map.region_count; i++) {
        memory_region_t *region = &memory_map.regions[i];
        if (region->type == MEMORY_AVAILABLE) {
            uint32_t start = region->start;
            uint32_t page_num = (0x300000 - start) / PAGE_SIZE;
            ppage_add_region(start, page_num);
        }
    }
}