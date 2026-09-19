#include <stdint.h>
#include <stddef.h>
#include "basic.h"

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void memcpy(void *dest, const void *src, size_t len) {
    char *d = dest;
    const char *s = src;

    while (len--)
        *d++ = *s++;
    return dest;
}
