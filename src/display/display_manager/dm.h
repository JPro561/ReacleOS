#include <stdbool.h>
#include <stdint.h>

#ifndef DM_H
#define DM_H

#define SECRET 97081459

typedef struct framebuffer {
    uintptr_t address;
    uint64_t pitch;
    uint64_t width;
    uint64_t height;
    uint64_t bpp;
} framebuffer;

bool dm_init();
bool draw_pixel(framebuffer *fb, uint64_t index, int col);

uint64_t token(int x, int y, int secret, framebuffer fb);
framebuffer getFramebuffer();

#endif
