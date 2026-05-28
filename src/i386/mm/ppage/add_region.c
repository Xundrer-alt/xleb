// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "debug.h"
#include "mm/mm.h"
#include "mm/ppage/mod.h"
#include "stdint.h"

void ppage_add_region(uint32_t start, uint32_t page_num) {
    DEBUG("region: start = 0x%x, page_num = %d", start, page_num);
    // TODO
}