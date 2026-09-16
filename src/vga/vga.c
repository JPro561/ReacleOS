#include <stdint.h>
#include <stddef.h>
#include "vga.h"

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void printchar(uint16_t *buffer, int y, int x, char cha, int color) {
    const size_t index = y * VGA_WIDTH + x;
    buffer[index] = (uint16_t) cha | color << 8;
}

void print_vga(uint16_t *buffer, int y, int x, char cha[], int color) {
    for (int i = 0; i < (int)strlen(cha); i++) {
        const size_t index = y * VGA_WIDTH + i + x;
        buffer[index] = (uint16_t) cha[i] | color << 8;
    }
}

void clear_vga(uint16_t *buffer) {
    for (int y = 0; y < (int)VGA_HEIGHT; y++) {
        for (int x = 0; x < (int)VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            buffer[index] = (uint16_t)' ' | (WHITE << 8);
        }
    }
}
