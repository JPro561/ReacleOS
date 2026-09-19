#include <stdint.h>

#ifndef FONTS_H
#define FONTS_H

static const char kbd_us_set1[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', /* Backspace */
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',    /* Enter */
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0,     /* Left Shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,                  /* Right Shift */
    '*',   0, ' ', /* Espaço */
    0,   /* Caps Lock */
    0,   /* F1 */
    0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   /* F2 - F10 */
    0,   /* Num Lock */
    0,   /* Scroll Lock */
    0,   /* Home */
    0,   /* Seta para Cima */
    0,   /* Page Up */
    '-',
    0,   /* Seta para Esquerda */
    0,
    0,   /* Seta para Direita */
    '+',
    0,   /* End */
    0,   /* Seta para Baixo */
    0,   /* Page Down */
    0,   /* Insert */
    0,   /* Delete */
    0,   0,   0,
    0,   /* F11 */
    0,   /* F12 */
};

extern const uint8_t font_8x16[128][16];

#endif
