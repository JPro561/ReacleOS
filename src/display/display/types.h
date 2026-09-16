#include <stdint.h>

#ifndef TYPES_H
#define TYPES_H

typedef struct {
    char title[32];
    int width;
    int height;
    int x;
    int y;
    uint32_t owner_pid;
} Window;

#endif
