OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)

ENTRY(_start)

SECTIONS
{
    . = 0xffffffff80100000;

    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.text .text.*)
    }

    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata .rodata.*)
    }

    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data .data.*)

        . = ALIGN(8);
        KEEP(*(.limine_requests_start))
        KEEP(*(.limine_requests))
        KEEP(*(.limine_requests_end))
    }

    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(.bss .bss.*)
        *(COMMON)
    }
}
