#include <stdint.h>
#include <stddef.h>

#ifndef VGA_H
#define VGA_H

#define VGA_MEM 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 20
#define VGA_BUFFER (uint16_t*)VGA_MEM;

enum vga_col {
    BLACK = 0,
    BLUE = 1,
	GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15,
};

size_t strlen(const char *str);
void printchar(uint16_t *buffer, int y, int x, char cha, int color);
void print_vga(uint16_t *buffer, int y, int x, char cha[], int color);
void clear_vga();

#endif
