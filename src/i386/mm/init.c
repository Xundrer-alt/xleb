#include "debug.h"
#include "halt.h"
#include "mm/mm.h"
#include "mm/lowlevel.h"

memory_map_t memory_map;

void mm_init() {
    INFO("memory manager: hello world");
    lowlevel_init();
    // TODO
}