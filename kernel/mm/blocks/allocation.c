#include "../../include/bool.h"
#include "../../internal/context_trace/kernel_ctx.h"
#include "context.h"
#include "../../internal/mem_int.h"

extern void print(char* texto);
extern void print_int(int valor);

void* mem_alloc(unsigned int size, unsigned char* terr_name) {
    ctx_push("mem_alloc");

    unsigned char* ptr = heap;

    int MIN_BLOCK = 16;

    Block* chosen = NULL;
    bool use_split = false;


    print("Procurando...\n");

    while (ptr < heap + heap_end) {

        Block* block = (Block*) ptr;

        unsigned char* next_block = ptr + sizeof(Block) + block->size;

        if (next_block > heap + heap_end) {
            ptr += sizeof(Block);
            continue;
        }

        if (!heap_check_block(block, heap, heap + heap_end)) {
            ptr += sizeof(Block) + block->size;
            continue;
        }

        if (block->size == 0) {
            ptr += sizeof(Block);
            continue;
        }

        if (block->size < size) {
            ptr += sizeof(Block) + block->size;
            continue;
        }

        if (block->free == 1 && block->size == size) {
            chosen = block;
            use_split = false;
            break;
        }

        if (block->free == 1 && block->size >= size + sizeof(Block)) {

            if (block->size >= size + sizeof(Block) + MIN_BLOCK) {
                chosen = block;
                use_split = true;
                break;
            } else {
                chosen = block;
                use_split = false;
                break;
            }
        }

        ptr = next_block;
    }

    if (chosen != NULL) {

        if (use_split) {

            unsigned int resto = chosen->size - size - sizeof(Block);

            if (resto >= MIN_BLOCK) {

                Block* new_block = (Block*)((unsigned char*)chosen + sizeof(Block) + size);

                new_block->id = active_blocks;
                new_block->magic = 0xDEADBEEF;
                new_block->size = resto;
                new_block->free = 1;
                new_block->state = BLOCK_OK;

                chosen->size = size;

                active_blocks++; // aumenta blocos ativos depois de bloco criado
            }
        }
        chosen->id = 0;
        chosen->free = 0;
        chosen->state = BLOCK_OK;

        print("\nAllocated ");
        print_int(chosen->size);
        print(" bytes\n");

        active_blocks++; // aumenta blocos ativos depois de bloco criado

        ctx_push("EXIT mem_alloc");
        return (void*)((unsigned char*)chosen + sizeof(Block));
    }

    if (heap_end + sizeof(Block) + size > HEAP_SIZE) {
        return 0;
    }

    Block* new_block = (Block*)(heap + heap_end);

    new_block->magic = 0xDEADBEEF;
    new_block->id = active_blocks;
    new_block->size = size;
    new_block->free = 0;
    new_block->state = BLOCK_OK;

    void* data = (void*)((unsigned char*)new_block + sizeof(Block));

    heap_end += sizeof(Block) + size;

    print("\nCreating new block\nAllocated ");
    print_int(size);
    print(" bytes\n");

    active_blocks++; // aumenta blocos ativos depois de bloco criado

    ctx_push("EXIT mem_alloc");
    return data;
}