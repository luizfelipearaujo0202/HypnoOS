#include "../../internal/context_trace/kernel_ctx.h"
#include "../../include/bool.h"
#include "../../internal/mem_int.h"

extern void print(char* texto);
extern void print_int(int valor);
extern void print_address(void* p);

void heap_debug() {
    ctx_push("ENTER heap_debug");
    unsigned char* ptr = heap;

    print("\n=== HEAP DEBUG ===\n");

    while (ptr < heap + heap_end) {
        Block* block = (Block*) ptr;
        
        print("[ BLOCK "), print_int(block->id), print("]\n");
        print("[ address = "), print_address(block), print(" ]\n");
        print("[ magic  = "); if(block->magic == 0xDEADBEEF) print("OK"); else print("CORRUPTED"); print(" ]\n");
        print("[ size = "), print_int(block->size), print(" ]\n");
        print("[ free = "); if (block->free == true) print("true"); else print("false"); print(" ]\n");
        print("[ state = "); if (block->state == BLOCK_OK) print("OK"); else print("CORRUPTED"); print(" ]\n\n");

        ptr = ptr + sizeof(Block) + block->size;

    print("\n=======================\n");
    }

    ctx_push("EXIT heap_debug");
}



void heap_status() {
    ctx_push("ENTER heap_status");
    unsigned char* ptr = heap;

    unsigned int largest_block = 0;
    unsigned int count = 0;
    unsigned int free_blocks = 0;

    while (ptr < heap + heap_end) {
        Block* block = (Block*) ptr;
        
        if (!block) return;

        if (block->free) {
            free_blocks++;
        }

        if (block->size > largest_block) {
            largest_block = block->size;
        }

        count++;

        ptr = ptr + sizeof(Block) + block->size;
    }

    print("\nHeap Used: "), print_int(heap_end);
    print("\nHeap Free: "), print_int(HEAP_SIZE - heap_end);
    print("\nBlocks: "), print_int(count);
    print("\nFree Blocks: "), print_int(free_blocks);
    print("\nLargest Block Size: "), print_int(largest_block);

    ctx_push("EXIT heap_status");
}