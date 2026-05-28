// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#pragma once
#include "list.h"
#define MAX_ORDER 16
struct free_area {
    struct list_head free_list;
};
extern struct free_area free_areas[MAX_ORDER + 1];

void ppage_add_region(uint32_t start, uint32_t page_num);
void ppage_init();