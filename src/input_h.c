#include <stdbool.h>
#include "input_h.h"
#include "basic.h"
#include "font.h"

bool input_handler(InputHandler *buffer) {
    if (buffer->count >= INPUT_BUFFER_SIZE) {
        return false; 
    }

    if ((inb(0x64) & 1) == 0) {
        return false;
    }

    int code = inb(0x60);

    int pos = buffer->head;

    buffer->data[pos] = code;
    buffer->head = (buffer->head + 1) % INPUT_BUFFER_SIZE;
    buffer->count++;

    return true;
}

bool input_pop(InputHandler *buffer, int *out_scancode) {
    if (buffer->count == 0) {
        return false; 
    }

    *out_scancode = buffer->data[buffer->tail];
    buffer->tail = (buffer->tail + 1) % INPUT_BUFFER_SIZE;
    buffer->count--;

    return true;
}

char getLetterPressed(InputHandler *i_h) {
    char letra = ' ';

    int scancode_recebido;

    while (input_pop(i_h, &scancode_recebido)) {
        if (scancode_recebido & 0x80) {
            continue; 
        }

        letra = kbd_us_set1[scancode_recebido];
    }

    return letra;
}
