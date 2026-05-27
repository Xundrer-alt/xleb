#pragma once
#define PHYS_TO_VIRT(x) ((x) + 0xC0000000)
#define VIRT_TO_PHYS(x) ((x) - 0xC0000000)