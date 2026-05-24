#include "debug.h"
#include "halt.h"
#include "memory/mm.h"
#include "memory/lowlevel.h"

memory_map_t memory_map;

void mm_init() {
    INFO("memory manager: hello world");
    lowlevel_init();
    // TODO
}