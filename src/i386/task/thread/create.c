// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "mm/kheap/mod.h"
#include "mm/ppage/mod.h"
#include "mm/virtconv.h"
#include "stddef.h"
#include "task/thread/mod.h"

#define STACK_SIZE 4096

thread_t* thread_create(void (*entry)()) {
    thread_t* thread = (thread_t*)kmalloc(sizeof(thread_t));
    if (!thread) return NULL;
    void* stack = (void*)PHYS_TO_VIRT((uint32_t)ppage_alloc(0));
    if (!stack) {
        kfree(thread);
        return NULL;
    }
    thread->stack_limit = stack;
    thread->state = THREAD_READY;
    uint32_t* esp = (uint32_t*)((uint8_t*)stack + STACK_SIZE);
    *(--esp) = (uint32_t)entry;
    *(--esp) = 0;
    *(--esp) = 0;
    *(--esp) = 0;
    *(--esp) = 0;
    *(--esp) = 0x202;
    thread->esp = esp;
    return thread;
}