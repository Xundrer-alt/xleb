// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
#include "boot/multiboot1/mod.h"
#include "debug.h"

void process_cmdline(const char *cmdline) {
    if (!cmdline) return;
    INFO("- cmdline: %s", cmdline);
}
