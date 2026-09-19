#include <stdbool.h>
#include <stdint.h>
#include "input_h.h"

#ifndef DM_H
#define DM_H

typedef struct framebuffer {
    uintptr_t address;
    uint64_t pitch;
    uint64_t width;
    uint64_t height;
    uint64_t bpp;
} framebuffer;

typedef struct {
    char title[32];
    int width;
    int height;
    int x;
    int y;
    uint32_t owner_pid;
} Window;

bool dm_init();
bool draw_pixel(framebuffer *fb, uint64_t index, int col);
framebuffer get_framebuffer();
void render(char buffer[], InputHandler *i_h, framebuffer *fb);
char getLetterPressed(InputHandler *i_h);

#endif
