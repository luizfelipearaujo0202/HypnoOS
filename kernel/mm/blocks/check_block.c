
#include "../../include/bool.h"
#include "../../internal/mem_int.h"


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