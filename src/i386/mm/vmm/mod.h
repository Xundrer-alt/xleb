// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#pragma once
#include "stdint.h"
#define PAGE_PRESENT  0x001
#define PAGE_WRITE    0x002
#define PAGE_USER     0x004
#define PAGE_WRITETHRU 0x008
#define PAGE_CACHE_DIS 0x010
#define PAGE_ACCESSED 0x020
#define PAGE_DIRTY    0x040
#define PAGE_PAT      0x080
#define PAGE_GLOBAL   0x100

void vmm_map_page(uint32_t *page_directory, uint32_t virt_addr, uint32_t phys_addr, uint32_t flags);