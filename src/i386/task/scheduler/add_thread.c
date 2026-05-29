// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "debug.h"
#include "task/scheduler/mod.h"
#include "task/thread/mod.h"

void scheduler_add_thread(void (*entry)()) {
    thread_t* thread = thread_create(entry);
    if (thread) {
        thread_queue[thread_count++] = thread;
    }
}