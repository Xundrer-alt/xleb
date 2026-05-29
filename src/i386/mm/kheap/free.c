// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "debug.h"
#include "mm/kheap/mod.h"
#include "stdint.h"

void kfree(void *ptr) {
    if (!ptr) return;
    heap_block_t *block = (heap_block_t*)((uint32_t)ptr - sizeof(heap_block_t));
    if (block->magic != 0xC0C0D0AF) {
        ERROR("kfree: invalid pointer 0x%x (magic=0x%x)", 
              (uint32_t)ptr, block->magic);
        return;
    }
    if (!block->used) {
        ERROR("kfree: double free at 0x%x", (uint32_t)ptr);
        return;
    }
    block->used = 0;
    heap_stats.used_size -= block->size;
    heap_stats.free_size += block->size;
    heap_stats.free_blocks++;
    // without merging for now
}