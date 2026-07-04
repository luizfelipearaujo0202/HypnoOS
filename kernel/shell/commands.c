#include "../internal/context_trace/kernel_ctx.h"
#include "../include/str_num.h"
#include "../mm/mem.h"

#define COMMAND_COUNT (sizeof(commands) / sizeof(Command))

typedef struct {
    const char* name;
    void (*handler)(void);
} Command;

void cmd_help();
void cmd_test(char* input);
void ping();

Command commands[] = {
    {"help", cmd_help},
    {"echo", cmd_test},
    {"test", cmd_test},
    {"ping", ping},
    {"trace", ctx_print},
    {"ctx", ctx_print},
    {"malloc", mem_alloc}
};

void execute_command(char* cmd) {
    for (int i = 0; i < COMMAND_COUNT; i++) {
        if (strcmp(cmd, commands[i].name) == 0) {
            commands[i].handler();
            return;
        }
    }

    print("Commando desconhecido.");
}

void cmd_help() {
    for (int i = 0; i < commands; i++) {
        print("Commands: \n");
        print_int(i), print("\n");
    }
}

void cmd_test(char* input) {
    char* letters[30];

    int argc = split(input, letters);

    for (int i = 1; i < argc; i++) {
        print(letters[i]);
        if (i < argc - 1) {
            print(" ");
        }
    }
}

void ping() {
    print("Pong!");
}