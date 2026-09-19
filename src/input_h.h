#include <stdint.h>
#include <stdbool.h>

#ifndef INPUT_H_H
#define INPUT_H_H

#define INPUT_BUFFER_SIZE 256

typedef struct InputHandler {
    uint32_t data[INPUT_BUFFER_SIZE];
    int head;
    int tail;
    int count;
} InputHandler;

typedef struct Key {
    uint16_t code;
    char name[64];
} Key;

bool input_handler(InputHandler *buffer);
bool input_pop(InputHandler *buffer, int *out_scancode);

#endif
