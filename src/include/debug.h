#pragma once
#include "stdarg.h"

void debug_putc(char c);
void debug_puts(const char *str);
void debug_print(const char *fmt, ...);

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

#define DEBUG(fmt, ...) \
debug_print("\033[36m[DEBUG] %s:%d: \033[0m" fmt "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)

#define INFO(fmt, ...) \
debug_print("\033[32m[INFO] \033[0m" fmt "\n", ##__VA_ARGS__)

#define WARNING(fmt, ...) \
debug_print("\033[33m[WARNING]: \033[0m" fmt "\n", ##__VA_ARGS__)

#define ERROR(fmt, ...) \
debug_print("\033[31m[ERROR]: \033[0m" fmt "\n", ##__VA_ARGS__)
