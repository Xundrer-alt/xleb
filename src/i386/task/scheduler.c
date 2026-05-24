#include "debug.h"
#include "halt.h"
#include "task/scheduler.h"
#include "task/thread.h"

static thread_t* thread_queue[16];
static int thread_count = 0;
thread_t* current_thread = NULL;
extern void switch_to(uint32_t** old_esp, uint32_t* new_esp);

void idle() {
    DEBUG("idle thread: hello world");
    while (1) {
        halt();
    }
}

void scheduler_add_thread(void (*entry)()) {
    thread_t* thread = thread_create(entry);
    if (thread) {
        thread_queue[thread_count++] = thread;
    }
}

void scheduler_init() {
    INFO("scheduler: hello world");
    current_thread = thread_create(idle);
    current_thread->state = THREAD_RUNNING;
    thread_queue[thread_count++] = current_thread;
}

void schedule() {
    if (thread_count == 0) return;
    thread_t* old_thread = current_thread;
    thread_t* next_thread = thread_queue[0]; 
    current_thread = next_thread;
    next_thread->state = THREAD_RUNNING;
    switch_to(&old_thread->esp, next_thread->esp);
}