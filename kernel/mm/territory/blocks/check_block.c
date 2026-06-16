
#include "../../include/bool.h"

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

static unsigned char heap[HEAP_SIZE];
static unsigned int heap_end = 0;


bool heap_check_block(Block* b, unsigned char* heap_start, unsigned char* heap_end) {
    if (!b) return false;

    if (b->size == 0 || b->size > (unsigned int)(heap_end - heap_start)) {
        b->state = BLOCK_CORRUPTED;
        return false;
    }

    if (b->free != 0 && b->free != 1) {
        b->state = BLOCK_CORRUPTED;
        return false;
    }

    unsigned char* ptr = (unsigned char*)b;

    unsigned char* next = ptr + sizeof(Block) + b->size;

    if (next > heap_end) {
        b->state = BLOCK_CORRUPTED;
        return false;
    }

    if (b->size > 0 && b->size < sizeof(Block)) {
        b->state = BLOCK_CORRUPTED;
        return false;
    }

    b->state = BLOCK_OK;
    return true;
}