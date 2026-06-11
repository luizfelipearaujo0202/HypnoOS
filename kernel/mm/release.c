#include "../internal/context_trace/kernel_ctx.h"
#include "../include/bool.h"
#include "../internal/mem.h"

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


void* mem_free(unsigned char* ptr) {
    ctx_push("ENTER mem_free");
    print("\nto rodano 2\n");
    Block* block = (Block*) ptr;
    block = ptr - sizeof(Block);

    unsigned char* pointer = heap;
    int error = 0;

    int block_id = 0;
    bool next_block_free = false;

    while (pointer < heap + heap_end) {
        if (block->id == block_id + 1) {

            if (block->free == true) {
                next_block_free = true;
            }
        }

        if (pointer == (unsigned char*)block) {
            block_id = block->id;

            break;
        }

        pointer = pointer + sizeof(Block) + block->size;
    }

    // ERROR 1
    error++;
    if (ptr == NULL) { // ponteiro nulo
        print("ERROR: "), print_int(error);
        print("\nFailed to free block "),  print_int(block->id), print(".\n");

        return;
    }

    // === VALIDAR BLOCO ===
    

    // ERROR 2
    error++;
    if (!block) {
        print("ERROR: "), print_int(error);
        print("\nFailed to free block "),  print_int(block->id), print(".\n");
    }

    // ERROR 3
    error++;
    if ((unsigned char*)block < heap || (unsigned char*)block >= heap + heap_end) {
        print("ERROR: "), print_int(error);
        print("\nFailed to free block "),  print_int(block->id), print(".\n");
    }

    // ERROR 4
    error++;
    if (block->size == 0 || block->size > heap_end) {
        print("ERROR: "), print_int(error);
        print("\nFailed to free block "),  print_int(block->id), print(".\n");
    }

    // ======

    bool check = heap_check_block(block, heap, heap + heap_end);

    // ERROR 5
    error++;
    if (check == false) { // se checagem der falso
        print("ERROR: "), print_int(error);
        print("\nFailed to free block "),  print_int(block->id), print(".\n");

        return;
    }

    // ERROR 6
    error++;
    if (block->state != BLOCK_OK) { // se está corrompido
        print("ERROR: "), print_int(error);
        print("\nFailed to free block "),  print_int(block->id), print(".\n");

        return;
    }

    // ERROR 7
    error++;
    if (block->free != 0 && block->free != 1) { // se realmente não está corrompido
        print("ERROR: "), print_int(error);
        print("\nFailed to free block "),  print_int(block->id), print(".\n");

        return;
    }

    // ERROR 8
    error++;
    if (block->free == true) { // se já está livre
        print("ERROR: "), print_int(error);
        print("\nFailed to free block "),  print_int(block->id), print(".\n");

        return;
    }

    if (block->free == false) {
        // ERROR 9
        if (block->magic != 0xDEADBEEF) {
            print("ERROR: "), print_int(error);
            print("\nFailed to free block "),  print_int(block->id), print(".\n");

            return;
        }
        else {
            block->free = true;
            print("\nBloco "), print_int(block->id), print(" free.\n");
            
            merge();

            return;
        }

    }

    ctx_push("EXIT mem_free");
}

void mem_free_by_id(unsigned int id) {
    ctx_push("ENTER mem_free_by_id");
    print("to rodano\n");
    unsigned char* ptr = heap;

    while (ptr < heap + heap_end) {
        Block* block = (Block*) ptr;

        if (block->id == id) {
            mem_free((unsigned char*)block + sizeof(Block));
            return;
        }

        ptr = ptr + sizeof(Block) + block->size;
    }

    ctx_push("EXIT mem_free_by_id");
}