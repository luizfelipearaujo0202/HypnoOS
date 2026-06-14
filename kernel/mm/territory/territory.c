/*--------------
 # TERRITÓRIOS #
 ---------------*/

#include "../../include/str_num.h"

#define HEAP_SIZE (4096 * 4096)

unsigned int heap[HEAP_SIZE];
unsigned char* end = heap + HEAP_SIZE;

typedef struct {
    char name[32];
    unsigned char* start;

    int priority;

    unsigned int size;
    unsigned int used;
    unsigned int limit;
    
} Territory;


#define MAX_TERRITORIES 4
static Territory territories[MAX_TERRITORIES];

unsigned int next_free_offset = 0;

void TerrInit() {
    int start_terr = (HEAP_SIZE / MAX_TERRITORIES) / 4;

    for (int i = 0; i < MAX_TERRITORIES; i++) {
        Territory* t = &territories[i];

        t->start = heap + (i * start_terr);
        t->size = start_terr;

        t->used = 0;
        t->limit = start_terr;

        if (i == 0) {
            t->priority = 10;
            strcpy(t->name, "Kernel");
        }

        if (i == 1) {
            t->priority = 5;
            strcpy(t->name, "Services");
        }

        if (i == 2) {
            t->priority = 3;
            strcpy(t->name, "User");
        }

        if (i == 3) {
            t->priority = 1;
            strcpy(t->name, "Sandbox");
        }

        next_free_offset += t->size;
    }
}

Territory* TerrCreate(const char* name, unsigned int size, int priority) {

    for (int i = 0; i < territories; i++) {
        Territory* t = &territories[i];

        if (t->used == 0) {
            unsigned char* start = heap + next_free_offset;

            t->start = start;
            t->size = size;
            t->used = 0;
            t->priority = priority;

            next_free_offset += size;
        }
    }
}