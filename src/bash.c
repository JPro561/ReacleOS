#include <stdbool.h>
#include "input_h.h"
#include "bash.h"
#include "basic.h"

void writeBuffer(char bash_buffer[BASH_BUFFER_SIZE], char text[], bool skip) {
    int c = 0;
    int count = 0;

    while (count < BASH_BUFFER_SIZE && bash_buffer[count] != '\0') {
        count++;
    }

    bash_buffer[count] = ' ';

    if (skip) {
        int ch = (count % BASH_WIDTH) + count;

        for (int i; i < ch; i++) {
            bash_buffer[i] = ' ';
        }
    }

    for (int i = 0; i < strlen(bash_buffer); i++) {
        bash_buffer[count] = ' ';

        count++;

        bash_buffer[count + i] = text[i];

        c = i;
    }

    bash_buffer[count + c] = '\0';
}

void clearBuffer(char bash_buffer[BASH_BUFFER_SIZE]) {
    for (int i; i < strlen(bash_buffer); i++) {
        bash_buffer[i] = ' ';
    }
}

bool runCmd(char bash_buffer[BASH_BUFFER_SIZE], char cmd[CMD_MAX_SIZE]) {
    if (cmd[0] == 'h') {
        if ((cmd[1] == 'e') && (cmd[2] == 'l') && (cmd[3] == 'p')) {
            writeBuffer(bash_buffer, "Teste", false);
            return true;
        }
    }
    return false;
}

bool teste_executado = false;

void updateBash(char buffer[BASH_BUFFER_SIZE], InputHandler *i_h) {
    clearBuffer(buffer);

    if (!teste_executado) {
        writeBuffer(buffer, "Teste bem testadaoooo\n", false);
        writeBuffer(buffer, "outro Teste bem testadaoooo", false);
        
        teste_executado = true;
    }
}
