// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "debug.h"
#include "halt.h"
#include "mm/kheap/mod.h"
#include "mm/mod.h"
#include "mm/ppage/mod.h"

void mm_init() {
    INFO("memory manager: hello world");
    ppage_init();
    kheap_init();
}