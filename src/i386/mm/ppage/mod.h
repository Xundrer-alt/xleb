// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#pragma once
#include "list.h"
#define MAX_ORDER 16
#define PAGE_SIZE 4096
enum page_flag {
    PAGE_FREE,
    PAGE_USED,
    PAGE_RESERVED
};
typedef struct free_block {
    struct free_block *next;
    unsigned int order;
} free_block_t;
struct page {
    struct list_head lru;
    uint32_t order;
    uint32_t flags;
};
extern free_block_t *free_lists[MAX_ORDER + 1];

void ppage_add_region(uint32_t start, uint32_t page_num);
void* ppage_alloc(uint32_t order);
void ppage_free(void *ptr, uint32_t order);
void ppage_init();