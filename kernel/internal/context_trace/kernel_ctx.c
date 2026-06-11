#define MAX_CTX 32

extern void print(char* texto);

static const char* ctx_stack[MAX_CTX];
static int ctx_top = -1;

void ctx_push(const char* name) {
    if (ctx_top < MAX_CTX - 1) {
        ctx_stack[++ctx_top] = name;
    }
}

void ctx_pop() {
    if (ctx_top >= 0)
        ctx_top--;
}

void ctx_print() {
    print("\n=== CONTEXT TRACE ===\n");

    for (int i = 0; i <= ctx_top; i++) {
        print(" -> ");
        print((char*)ctx_stack[i]);
        print("\n");
    }
}