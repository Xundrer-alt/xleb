#include "debug.h"
#include "halt.h"
#include "memory/mm.h"
#include "memory/lowlevel.h"

memory_map_t memory_map;

void mm_init() {
    INFO("memory manager: hello world");
    lowlevel_init();
    // Lowlevel allocator (stack based) test
    uint32_t *ptr = lowlevel_alloc();
    uint32_t *ptr2 = lowlevel_alloc();
    uint32_t *ptr3 = lowlevel_alloc();
    if (ptr == NULL || ptr2 == NULL || ptr3 == NULL) {
        ERROR("Out of memory!");
        return;
    }
    *ptr = 12345;
    *ptr2 = 54321;
    *ptr3 = 0xDEADBEEF;
    DEBUG("TEST: *ptr = %d, *ptr2 = %d, *ptr3 = 0x%x", *ptr, *ptr2, *ptr3);
}