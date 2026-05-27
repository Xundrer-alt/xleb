#include "debug.h"
#include "halt.h"
#include "mm/lowlevel.h"
#include "mm/mm.h"

static uint32_t* stack_ptr;
static int stack_top = -1;
static int max_stack_size = 0;

void lowlevel_init() {
    uint32_t start = (uint32_t)&_kernel_end;
    stack_ptr = (uint32_t*)((start + 3) & ~3);
    uint32_t end = PHYS_TO_VIRT(LOWLEVEL_LIMIT);
    uint32_t first_page = (start + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);

    stack_top = -1;
    max_stack_size = (end - first_page) / PAGE_SIZE;

    for (uint32_t addr = first_page; addr + PAGE_SIZE <= end; addr += PAGE_SIZE) {
        stack_ptr[++stack_top] = addr; 
    }

    DEBUG("Lowlevel pages available: %d", stack_top + 1);
}

void* lowlevel_alloc() {
    if (stack_top < 0) return NULL;
    return (void*)stack_ptr[stack_top--];
}

void lowlevel_free(void* ptr) {
    if (stack_top >= max_stack_size - 1) {
        ERROR("Attempt to Double Free or Stack Overflow");
        halt();
    }
    stack_ptr[++stack_top] = (uint32_t)ptr;
}