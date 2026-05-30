// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#pragma once

#define LMEM_MAX_SIZE (32 * 1024 * 1024)
#define LMEM_START_PADDR 0x400000
#define LMEM_PDE_SIZE (4 * 1024 * 1024)

void map_lmem();