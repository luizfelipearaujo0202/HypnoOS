#include "../include/str.h"

extern void print(char* texto);

void shell_execute(char *line) {
    char *commands[] = {"echo", "test", "help", "ping", "clear", "kmalloc"};

    char *argv[15];

    int argc = split(line, argv);

    if (argc == 0) {
        return;
    }

    if (argc >= 1) {
        print("\n");

        if (strcmp(argv[0], "echo") == 0 || strcmp(argv[0], "test") == 0) {
            for (int i = 1; i < argc; i++) {
                print(argv[i]);

                if (i < argc - 1) {
                    print(" ");
                }
            }
        }

        else if (strcmp(argv[0], "help") == 0) {
            print("Commands: \n");
            for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
                print(commands[i]);
            }
        }

        else if (strcmp(argv[0], "ping") == 0) {
            print("Pong!");
        }

        else if (strcmp(argv[0], "clear") == 0) {
            print("Cleared");
        }

        else {
            print("command not found");
        }
    }
}