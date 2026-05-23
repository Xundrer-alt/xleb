#pragma once

typedef enum {
    MEMORY_AVAILABLE = 1,
    MEMORY_RESERVED = 2,
    MEMORY_ACPI_RECLAIMABLE = 3,
    MEMORY_ACPI_NVS = 4,
    MEMORY_BADRAM = 5
} memory_type_t;

typedef struct {
    uint32_t start;
    uint32_t end;
    uint32_t size;
    memory_type_t type;
} memory_region_t;

#define PHYS_TO_VIRT(x) ((x) + 0xC0000000)