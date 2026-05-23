ENTRY(_entry)

SECTIONS
{
    . = 1M;

    .text : AT(ADDR(.text)) {
        *(.multiboot)
        *(.text)
        *(.text.*)
    }

    .data : AT(ADDR(.data)) {
        *(.data)
        *(.data.*)
    }

    .rodata : AT(ADDR(.rodata)) {
        *(.rodata)
        *(.rodata.*)
    }

    .bss : AT(ADDR(.bss)) {
        *(COMMON)
        *(.bss)
        *(.bss.*)
    }

    . = ALIGN(4K);
}
