#include "memory/lowlevel.h"
#include "stddef.h"
#include "task/thread.h"

#define STACK_SIZE 4096

thread_t* thread_create(void (*entry)()) {
    thread_t* thread = (thread_t*)lowlevel_alloc();
    if (!thread) return NULL;
    void* stack = lowlevel_alloc();
    if (!stack) {
        lowlevel_free(thread);
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