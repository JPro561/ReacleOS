#include <stdint.h>
#include <stddef.h>

#ifndef BASIC_H
#define BASIC_H

static inline unsigned char inb(unsigned short port) {
    unsigned char value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static inline void outb(unsigned short port, unsigned char value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

size_t strlen(const char *str);
void memcpy(void *dest, const void *src, size_t n);

#endif
