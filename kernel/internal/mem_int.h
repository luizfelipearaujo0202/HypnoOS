#ifndef MEM_INT_H
#define MEM_INT_H

// HEAP

#define HEAP_SIZE (4096 * 4096)

unsigned char heap[HEAP_SIZE];
unsigned int heap_end = 0;

// BLOCKS

unsigned int active_blocks = 1;

typedef enum {
    BLOCK_OK = 0,
    BLOCK_CORRUPTED = 1
} BlockState;

#define BLOCK_MAGIC 0xDEADBEEF

typedef struct Block {
    unsigned int magic;

    unsigned int id;

    unsigned int size;
    unsigned char free;

    BlockState state;
} Block;   

// PAGES

#define PAGE_SIZE 1024
#define TOTAL_PAGES (HEAP_SIZE / PAGE_SIZE)


#endif