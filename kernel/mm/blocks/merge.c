#include "../../include/bool.h"
#include "../../internal/context_trace/kernel_ctx.h"
#include "../../internal/mem_int.h"

extern void print(char* texto);
extern void print_int(int valor);


void merge() {
    ctx_push("ENTER merge");
    unsigned char* ptr = heap;

    print("\nVerificando possivel merge...\n");
    while (ptr < heap + heap_end) {
        Block* block = (Block*)ptr;

        Block* next = (Block*)((unsigned char*)block + sizeof(Block) + block->size);

        if ((unsigned char*)next >= heap + heap_end) {
            break;
        }

        if (block->free && next->free) {
            block->size += sizeof(Block) + next->size;
            active_blocks--;
            
            continue;
        }

        ptr = (unsigned char*)block + sizeof(Block) + block->size;
    }
    print("Verificação concluida.\n");

    ctx_push("EXIT merge");
}