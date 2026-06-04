#include "../include/terminal.h"

extern void shell_execute(char *line);
extern void print(char* texto);
extern void print_char(char c);

extern int strlen(char *texto);

static char buffer[128];
static int i = 0;

char* terminal_readline(char* prompt) {
    print("\nTA NO TERMINAL READLINE\n");

    bool line_ready = false;
    terminal_state.busy = false;

    char c;

    print(prompt);

    while(!(line_ready)) {
        if (c == '\b') {
             if (i > strlen(prompt)) {
                i--;
                print_char('\b');
                print_char(' ');
                print_char('\b');
             }
        }

        else if (c == '\n') {
            buffer[i] = '\0';
            line_ready = true;
        }

        else {
            if (i < 127) {
                buffer[i] = c;
                print_char(buffer[i]);
                print(buffer);
                i++;
            }
        }
    }
    shell_execute(buffer);
    i = 0;
    return buffer;
}