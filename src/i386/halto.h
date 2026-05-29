// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt

#pragma once

static inline void halt() {
    while (1) {
        __asm__ volatile ("hlt");
    }
}