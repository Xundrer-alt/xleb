#pragma once

static inline void halt() {
    while (1) {
        __asm__ volatile ("hlt");
    }
}