// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "debug.h"
#include "mm/mm.h"
#include "mm/virtconv.h"
#include "mm/ppage/mod.h"
#include "stdint.h"

static void add_to_free_list(uint32_t start, unsigned int order) {
    free_block_t *block = (free_block_t*)PHYS_TO_VIRT(start); // PHYS_TO_VIRT make address virtual, not physical (so "ppage" isn't ppage)
    block->order = order;
    block->next = free_lists[order];
    free_lists[order] = block;
}

void ppage_add_region(uint32_t start, uint32_t page_num) {
    uint32_t remaining = page_num;
    uint32_t current = start;
    while (remaining > 0) {
        uint32_t order = 0;
        uint32_t block_size = 1;
        while (block_size <= remaining && order < MAX_ORDER) {
            uint32_t block_bytes = block_size * PAGE_SIZE;
            if ((current & (block_bytes - 1)) == 0) {
                order++;
                block_size <<= 1;
            } else {
                break;
            }
        }
        if (order > 0) {
            order--;
            block_size >>= 1;
        }
        add_to_free_list(current, order);
        current += block_size * PAGE_SIZE;
        remaining -= block_size;
    }
}