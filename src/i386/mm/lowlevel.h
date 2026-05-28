// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#pragma once
#include "mm/mm.h"
#include "stdint.h"
#define LOWLEVEL_LIMIT (uint32_t)0x400000
extern uint32_t _kernel_end;

void lowlevel_init();
void* lowlevel_alloc();
void lowlevel_free(void* ptr);