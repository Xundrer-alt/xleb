// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#pragma once

typedef enum {
    THREAD_READY,
    THREAD_RUNNING,
    THREAD_DEAD
} thread_state_t;

typedef struct {
    uint32_t edi, esi, ebx, ebp, eip;
} thread_context_t;

typedef struct {
    uint32_t id;
    thread_state_t state;
    void* stack_limit;
    uint32_t* esp;
} thread_t;

extern thread_t* current_thread;
thread_t* thread_create(void (*entry)());