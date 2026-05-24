#pragma once
#include "memory/mm.h"
#include "stdint.h"
#define LOWLEVEL_LIMIT (uint32_t)0x400000
extern uint32_t _kernel_end;

void lowlevel_init();
void* lowlevel_alloc();
void lowlevel_free(void* ptr);