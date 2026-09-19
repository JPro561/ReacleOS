#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "include/limine.h"
#include "render.h"
#include "basic.h"
#include "font.h"
#include "input_h.h"
#include "bash.h"

#define MAX_WIDTH  3840
#define MAX_HEIGHT 2160
#define MAX_PIXELS (MAX_WIDTH * MAX_HEIGHT)

static uint32_t back_buffer[MAX_PIXELS];

__attribute__((used)) static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

framebuffer fb;

void flip(framebuffer *fb) {
    if (fb->pitch == (uint64_t)fb->width * 4) {
        memcpy((void *)fb->address, back_buffer, fb->width * fb->height * sizeof(uint32_t));
    } else {
        uint8_t *dest_line = (uint8_t *)fb->address;
        uint8_t *src_line = (uint8_t *)back_buffer;
        if (dest_line != src_line) {
            for (int y = 0; y < fb->height; y++) {
                memcpy(dest_line, src_line, fb->width * sizeof(uint32_t));
                dest_line += fb->pitch;
                src_line += fb->width * sizeof(uint32_t);
            }
        }
    }
}

framebuffer get_framebuffer() {
    return fb;
}

bool draw_char(framebuffer *fb, char c, int x, int y, uint32_t color) {
    uint8_t* glyph = font_8x16[(unsigned char)c];

    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 8; col++) {
            if (glyph[row] & (0x80 >> col)) {
                int x_r = x + col;
                int y_r = y + row;
                back_buffer[x_r + (y_r * fb->width)] = color;
            }
        }
    }
}

// REAL PROCESS

void render(char buffer[], InputHandler *i_h, framebuffer *fb) {
    int pixels = fb->width * fb->height;
    int linha = 0;

    for (int i = 0; i < pixels; i++) {
        if (back_buffer[i] != 0x000000) {
            back_buffer[i] = 0x000000;
        }
    }
    
    char letra = getLetterPressed(i_h);

    int lin = 0;
    int col = 0;

    for (int i = 0; i < BASH_BUFFER_SIZE; i++) {
        if (buffer[i] == '\0') {
            continue;
        }

        if (buffer[i] == '\n') {
            lin++;
            col = 0;
            continue;
        }

        int y = (lin / BASH_WIDTH) * 16;
        int x = (col % BASH_WIDTH) * 8;

        if (x + 8 <= fb->width && y + 16 <= fb->height) {
            draw_char(fb, buffer[i], x, y, 0xFFFFFF);
        }

        if (col >= BASH_WIDTH) {
            col = 0;
            lin++;
        }
    }

    flip(fb);
}

bool dm_init() {
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        return false;
    }

    fb = (framebuffer){
        .address = (uintptr_t)framebuffer_request.response->framebuffers[0]->address,
        .pitch = framebuffer_request.response->framebuffers[0]->pitch,
        .width = framebuffer_request.response->framebuffers[0]->width,
        .height = framebuffer_request.response->framebuffers[0]->height,
        .bpp = framebuffer_request.response->framebuffers[0]->bpp,
    };

    if (fb.width > MAX_WIDTH || fb.height > MAX_HEIGHT) {
        return false;
    }

    return true;
}
