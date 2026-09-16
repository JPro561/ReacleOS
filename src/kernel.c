#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga/vga.h"
#include "asm.h"
#include "display/display_manager/dm.h"
#include "display/display/display.h"

uint16_t *vga_buffer;

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

    display();

    for (;;) { __asm__("hlt"); }
}
