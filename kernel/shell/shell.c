#include "../include/str.h"

extern void print(char* texto);

void shell_execute(char *line) {
    print("\nCHEGOU NO SHELL\n");
    char *argv[15];

    int argc = split(line, argv);

    if (strcmp(argv[0], "echo") == 0) {
        print(argv[1]);
    }

    else if (strcmp(argv[0], "clear") == 0) {
    }

    else {
        print("command not found\n");
    }
}