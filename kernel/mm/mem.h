#ifndef mem
#define mem

void* mem_alloc(unsigned int size);
void mem_free_by_id(unsigned int id);
void heap_debug();
void heap_status();
void merge();

void page_init();
int page_alloc(size);

#endif