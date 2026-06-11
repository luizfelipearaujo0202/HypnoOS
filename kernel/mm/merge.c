#include "../include/bool.h"

typedef enum {
    BLOCK_OK = 0,
    BLOCK_CORRUPTED = 1
} BlockState;
typedef struct Block {
    unsigned int magic;
    unsigned int id;
    unsigned int size;
    unsigned char free;
    BlockState state;
} Block;

#define HEAP_SIZE (1024 * 1024)

extern void print(char* texto);
extern void print_int(int valor);

extern unsigned char heap[HEAP_SIZE];
extern unsigned int heap_end;

extern unsigned int active_blocks;



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
            block;
            block->size += sizeof(Block) + next->size;
            active_blocks--;
            
            continue;
        }

        ptr = (unsigned char*)block + sizeof(Block) + block->size;
    }
    print("Verificação concluida.\n");

    ctx_push("EXIT merge");
}