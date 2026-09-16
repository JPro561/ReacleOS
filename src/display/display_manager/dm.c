#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "../../include/limine.h"
#include "../display/display.h"
#include "dm.h"

__attribute__((used)) static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

uint64_t token(int x, int y, int secret, framebuffer fb) {
    return ((y * fb.pitch / 4) + x) * secret;
}

framebuffer fb;

bool draw_pixel(framebuffer *fb, uint64_t index, int col) {
    if (index % SECRET != 0) {
        return false;
    }
    
    index = index / SECRET;

    uint64_t bytes_per_pixel = fb->bpp / 8;

    uint64_t y = index / (fb->pitch / bytes_per_pixel);
    uint64_t x = index % (fb->pitch / bytes_per_pixel);

    if (!((float)y == (int)y) && !((float)x == (int)x)) {
        return false;
    }

    if ((y >= fb->height) || (x >= fb->width)) {
        return false;
    }

    uint32_t *fb_ptr = (uint32_t *)fb->address;
    fb_ptr[index] = col;

    return true;
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

    display();
}

framebuffer getFramebuffer() {
    return fb;
};
