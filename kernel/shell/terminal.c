#include "../include/terminal.h"

extern void shell_execute(char *line);
extern void print(char* texto);
extern void print_char(char c);

extern int strlen(char *texto);

extern void kbhandler_c();

static char buffer[128];
static int i = 0;
static bool line_ready = false;

char* terminal_readline(char* prompt) {
    line_ready = false;
    terminal_state.busy = false;
    i = 0;

    print(prompt);

    while (!line_ready) {
        __asm__ volatile("hlt");
    }

    shell_execute(buffer);
    i = 0;
    return buffer;
}

void terminal_input(char c) {
    if (c == '\n') {
        buffer[i] = '\0';
        line_ready = true;
    }
    else if (c == '\b') {
        if (i > 0) i--;
        buffer[i] = '\0';
    }
    else {
        if (i < 127) {
            buffer[i] = c;
            i++;
        }
    }
}