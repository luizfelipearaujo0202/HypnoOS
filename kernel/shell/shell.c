#include "../internal/context_trace/kernel_ctx.h"
#include "../include/str_num.h"
#include "../mm/mem.h"

extern void print(char* texto);
extern void print_int(int valor);

void shell_execute(char *line) {
    char *commands[] = {"echo", "test", "help", "ping", "clear"};

    char *argv[30];

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
            for (int i = 1; i < argc; i++) {
                if (is_number(argv[i])) {
                    int size = atoi_simple(argv[i]);
                    // mem_alloc(size);
                }
            }
        }

        else if (strcmp(argv[0], "palloc") == 0) {
            if (is_number(argv[1])) {
                int size = argv[1];
                int pages = page_alloc(size);

                if (pages <= 0) {
                    print("\n");
                } else {
                print("Alocatted "), print_int(pages), print(" pages.");
                }
            }
        }

        else if (strcmp(argv[0], "kfree") == 0) {
            for (int i = 1; i < argc; i++) {
                if (is_number(argv[i])) {
                    int id = atoi_simple(argv[i]);
                    // mem_free_by_id(id);
                }
            }
        }
            else if (strcmp(argv[1], "block") == 0) {
                for (int i = 2; i < argc; i++) {
                if (is_number(argv[i])) {
                    int id = atoi_simple(argv[i]);
                    // mem_free_by_id(id);
                }
            }
        }

        else if (strcmp(argv[0], "hdebug") == 0) {
            //heap_debug();
        }

        else if (strcmp(argv[0], "hstats") == 0) {
            //heap_status();
        }

        else if (strcmp(argv[0], "ctx") == 0 || strcmp(argv[0], "trace") == 0) {
            ctx_print();
        }

        else if (strcmp(argv[0], "clear") == 0) {
            for (int i = 0; i < 80; i++) {
                print("\n");
            }
            print("Cleared");
            print("\n");
        }

        else {
            print("command not found");
        }
    }
}