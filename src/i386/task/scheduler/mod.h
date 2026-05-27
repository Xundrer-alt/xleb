#pragma once
#include "task/thread/mod.h"

extern thread_t* thread_queue[16];
extern int thread_count;
extern thread_t* current_thread;

void scheduler_add_thread(void (*entry)());
void scheduler_init();
void schedule();