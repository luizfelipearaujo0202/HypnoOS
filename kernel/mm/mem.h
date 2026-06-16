#ifndef mem
#define mem

#include "../include/bool.h"
typedef struct {
    char name[32];

    unsigned int magic;

    unsigned char* start;

    int priority;

    unsigned int size;
    unsigned int used;
    unsigned int limit;

    unsigned int next_offset;

    bool active;
    
} Territory;


//void* mem_alloc(unsigned int size);
//void mem_free_by_id(unsigned int id);
//void heap_debug();
//void heap_status();
//void merge();

void page_init();
int page_alloc(size);

void TerrInit();
Territory* TerrCreate(const char* name, unsigned int size, int priority);
Territory* TerrDestroy(const char* name);
int TerrCount();
Territory* TerrFinder(const char* name);
void TerrDebug();


#endif