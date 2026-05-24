#include "debug.h"
#include "iob.h"

void debug_putc(char c) {
    while (!(inb(0x3F8 + 5) & (1 << 5)));
    if (c == '\n') {
        debug_putc('\r');
    }
    outb(0x3F8, c);
}

void debug_puts(const char *str) {
    while (*str) {
        debug_putc(*str++);
    }
}

static void print_num(int num, int is_signed) {
    if (is_signed && num < 0) {
        debug_putc('-');
        num = -num;
    }

    if (num >= 10) {
        print_num(num / 10, 0);
    }
    debug_putc('0' + (num % 10));
}

static void print_hex(unsigned int num) {
    static const char hex[] = "0123456789abcdef";

    for (int i = 28; i >= 0; i -= 4) {
        debug_putc(hex[(num >> i) & 0xF]);
    }
}

void debug_print(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 's': {
                    const char *str = va_arg(args, const char*);
                    while (*str) {
                        debug_putc(*str++);
                    }
                    break;
                }
                case 'd': {
                    int num = va_arg(args, int);
                    print_num(num, 1);
                    break;
                }
                case 'u': {
                    int num = va_arg(args, unsigned int);
                    print_num(num, 0);
                    break;
                }
                case 'x': {
                    unsigned int num = va_arg(args, unsigned int);
                    print_hex(num);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    debug_putc(c);
                    break;
                }
                case '%': {
                    debug_putc('%');
                    break;
                }
                default:
                    debug_putc('%');
                    debug_putc(*fmt);
                    break;
            }
        } else {
            debug_putc(*fmt);
        }
        fmt++;
    }
    va_end(args);
}
