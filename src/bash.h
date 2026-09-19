#ifndef BASH_H
#define BASH_H

#define BASH_BUFFER_SIZE 8192
#define CMD_MAX_SIZE 1024
#define BASH_HEIGHT 24
#define BASH_WIDTH 80

void updateBash(char buffer[BASH_BUFFER_SIZE], InputHandler *i_h);

#endif
