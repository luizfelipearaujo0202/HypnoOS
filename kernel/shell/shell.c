#include "../include/str.h"

extern void print(char* texto);
extern void* kmalloc(unsigned int size);
extern void heap_debug();

void shell_execute(char *line) {
    char *commands[] = {"echo", "test", "help", "ping", "clear"};

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
                print("\n");
            }
        }

        else if (strcmp(argv[0], "ping") == 0) {
            print("Pong!");
        }

        else if (strcmp(argv[0], "kmalloc") == 0) {
            if (is_number(argv[1])) {
                int size = atoi_simple(argv[1]);
                kmalloc(size);
            }
        }

        else if (strcmp(argv[0], "hdebug") == 0) {
            heap_debug();
        }

        else if (strcmp(argv[0], "clear") == 0) {
            print("Cleared");
        }

        else {
            print("command not found");
        }
    }
}