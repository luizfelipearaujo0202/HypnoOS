#ifndef mem
#define mem

#include "../include/bool.h"
#include "../internal/mem_int.h"

bool heap_check_block(Block* b, unsigned char* heap_start, unsigned char* heap_end);

void* mem_alloc(unsigned int size);
void mem_free_by_id(unsigned int id);

void heap_debug();
void heap_status();

void merge();

void page_init();
int page_alloc(int size);


#endif