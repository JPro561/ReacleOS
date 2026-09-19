#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga/vga.h"
#include "basic.h"
#include "render.h"
#include "input_h.h"
#include "bash.h"

uint16_t *vga_buffer;

static InputHandler input_buffer;
char bash_buffer[BASH_BUFFER_SIZE];

// INIT KERNEL
void init_kernel() {
    vga_buffer = (uint16_t*)VGA_MEM;
}

void _start() {
    init_kernel();

    if (!dm_init()) {
        print_vga(vga_buffer, VGA_HEIGHT / 2 + 1, VGA_WIDTH / 2 - (strlen("KERNEL ERROR: Limine Framebuffer Failed") / 2), "KERNEL ERROR: Limine Framebuffer Failed", LIGHT_RED);
        print_vga(vga_buffer, VGA_HEIGHT / 2 + 3, VGA_WIDTH / 2 - (strlen("If you don't know what this error means,") / 2), "If you don't know what this error means,", WHITE);
        print_vga(vga_buffer, VGA_HEIGHT / 2 + 4, VGA_WIDTH / 2 - (strlen("Just restart your pc by pressing enter") / 2), "Just restart your PC by pressing enter", WHITE); 

        for (;;) {
            unsigned char scancode = inb(0x60); 
            
            if (scancode == 0x1C) {
                break;
            }
            
            __asm__ volatile("pause");
        }

        outb(0x64, 0xFE);

        for (;;) { __asm__("hlt"); }
    }

    framebuffer fb = get_framebuffer();

    for (;;) {
        input_handler(&input_buffer);
        updateBash(bash_buffer, &input_buffer);
        render(bash_buffer, &input_buffer, &fb);
    }

    for (;;) { __asm__("hlt"); }
}
