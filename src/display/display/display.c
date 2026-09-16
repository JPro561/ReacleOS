#include "../display_manager/dm.h"
#include "display.h"
#include "types.h"

void display() {
    framebuffer fb = getFramebuffer();

    int y = 0;
    int x = 0;
    while (y < (int)fb.height) {
        while (x < (int)fb.width) {
            draw_pixel(&fb, token(x, y, SECRET, getFramebuffer()), 0x90D5FFFF);
            x++;
        }
        y++;
        x = 1;
    }
}
