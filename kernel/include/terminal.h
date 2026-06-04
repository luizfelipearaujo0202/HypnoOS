#ifndef Terminal_H
#define Terminal_H

#include "bool.h"

void terminal_input(char c);

typedef struct {
    bool busy;
    int current_job_id;
} TerminalState;

extern TerminalState terminal_state;

#endif 