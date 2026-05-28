// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "debug.h"
#include "mm/virtconv.h"
#include "mm/ppage/mod.h"
#include "stdint.h"

void ppage_free(void *ptr, unsigned int order) {
    if (ptr == NULL) {
        ERROR("ppage_free: NULL pointer");
        return;
    }
    if (order > MAX_ORDER) {
        ERROR("order %d > MAX_ORDER %d", order, MAX_ORDER);
        return;
    }
    free_block_t *block = (free_block_t*)ptr;
    block->order = order;
    uint32_t current_order = order;
    uint32_t block_virt = (uint32_t)ptr;
    while (current_order < MAX_ORDER) {
        uint32_t block_size = (1 << current_order) * PAGE_SIZE;
        uint32_t buddy_virt = block_virt ^ block_size;
        free_block_t *prev = NULL;
        free_block_t *curr = free_lists[current_order];
        int found = 0;
        while (curr != NULL) {
            if ((uint32_t)curr == buddy_virt && curr->order == current_order) {
                if (prev == NULL) {
                    free_lists[current_order] = curr->next;
                } else {
                    prev->next = curr->next;
                }
                found = 1;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        if (!found) {
            break;
        }
        if (buddy_virt < block_virt) {
            block = (free_block_t*)buddy_virt;
            block_virt = buddy_virt;
        }
        current_order++;
        block->order = current_order;
    }
    block->next = free_lists[current_order];
    free_lists[current_order] = block;
}