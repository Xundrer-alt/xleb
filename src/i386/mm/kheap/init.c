// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "debug.h"
#include "rust_ffi.h"
#include "mm/kheap/mod.h"
#include "mm/ppage/mod.h"
#include "mm/virtconv.h"
#include "stddef.h"
#include "stdint.h"
#include "string.h"

heap_block_t *heap_start = NULL;
uint32_t heap_brk = 0;
heap_stats_t heap_stats = {0};

int expand_heap() {
    uint32_t ppage = (uint32_t)ppage_alloc(0);
    if (!ppage) {
        ERROR("kheap: failed to allocate physical page");
        return -1;
    }
    uint32_t vpage = PHYS_TO_VIRT(ppage); // returns first free paddr + 0xC0000000, may be non-contiguous
    if (vpage & (PAGE_SIZE - 1)) {
        ERROR("kheap: unaligned page! phys=0x%x, virt=0x%x", ppage, vpage);
        return -1;
    }
    if (heap_brk == 0) {
        heap_brk = vpage;
        heap_start = (heap_block_t*)heap_brk;
    }
    heap_block_t *new_block = (heap_block_t*)vpage;
    new_block->magic = 0xC0C0D0AF;
    new_block->size = PAGE_SIZE - sizeof(heap_block_t);
    new_block->used = 0;
    new_block->next = NULL;
    new_block->prev = NULL;
    if (heap_start != new_block) {
        heap_block_t *last = heap_start;
        while (last->next) {
            last = last->next;
        }
        last->next = new_block;
        new_block->prev = last;
    }
    heap_brk = vpage + PAGE_SIZE;
    heap_stats.total_size += PAGE_SIZE;
    heap_stats.free_size += new_block->size;
    heap_stats.blocks_count++;
    heap_stats.free_blocks++;
    return 0;
}

void kheap_init() {
    memset(&heap_stats, 0, sizeof(heap_stats_t));
    int pages_allocated = 0;
    for (int i = 0; i < KHEAP_INITIAL_PAGES; i++) {
        if (expand_heap() != 0) {
            ERROR("kheap: failed to allocate initial page %d", i);
            break;
        }
        pages_allocated++;
    }
    if (pages_allocated == 0) {
        ERROR("kheap: failed to allocate any memory");
        halt();
    }
    heap_block_t *current = heap_start;
}