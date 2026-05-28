// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "debug.h"
#include "mm/mm.h"
#include "mm/virtconv.h"
#include "mm/ppage/mod.h"
#include "stdint.h"

void* ppage_alloc(uint32_t order) {
    if (order > MAX_ORDER) {
        ERROR("order %d > MAX_ORDER %d", order, MAX_ORDER);
        return NULL;
    }
    uint32_t current_order = order;
    while (current_order <= MAX_ORDER) {
        if (free_lists[current_order] != NULL) {
            free_block_t *block = free_lists[current_order];
            free_lists[current_order] = block->next;
            while (current_order > order) {
                current_order--;
                uint32_t block_size = (1 << current_order) * PAGE_SIZE;
                free_block_t *buddy = (free_block_t*)((uint32_t)block + block_size);
                buddy->order = current_order;
                buddy->next = free_lists[current_order];
                free_lists[current_order] = buddy;
            }
            return (void*)block;
        }
        current_order++;
    }
    return NULL;
}