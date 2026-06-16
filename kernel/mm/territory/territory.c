/*--------------
 # TERRITÓRIOS #
 ---------------*/

#include "../../include/str_num.h"
#include "../../include/bool.h"
#include "../../internal/context_trace/kernel_ctx.h"

#define HEAP_SIZE (4096 * 4096)

#define TERR_USED 0x54455252
#define TERR_FREE 0x0

unsigned int heap[HEAP_SIZE];
unsigned char* end = heap + HEAP_SIZE;

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


Territory* TerrCreate(const char* name, unsigned int size, int priority);


#define MAX_TERRITORIES 4
Territory territories[MAX_TERRITORIES];

unsigned int next_free_offset = 0;
unsigned int terr_count = 0;

void TerrInit() {
    ctx_push("[Enter] TerrInit");
    
    int start_terr = (HEAP_SIZE / MAX_TERRITORIES) / 4;

    TerrCreate("Kernel", start_terr, 10);
    TerrCreate("Services", start_terr, 5);
    TerrCreate("User", start_terr, 3);
    TerrCreate("Sandbox", start_terr, 1);

    print("\nCreated "), print_int(terr_count), print(" territories.\n");

    ctx_push("[Exit] TerrInit");
}



Territory* TerrCreate(const char* name, unsigned int size, int priority) { // Criar território
    ctx_push("[Enter] TerrCreate");

    for (int i = 0; i < MAX_TERRITORIES; i++) {
        Territory* t = &territories[i];

        if (t->magic != TERR_USED) {
            unsigned char* start = heap + t->next_offset;

            strcpy(t->name, name);

            t->magic = TERR_USED;

            t->start = start;
            t->size = size;
            t->used = 0;
            t->priority = priority;
            t->active = true;

            t->next_offset += size;
            
            terr_count++;

            ctx_push("[Exit] TerrCreate");
            return t;
        }
    }
}



void TerrDestroy(const char* name) { // Limpar território
    ctx_push("[Enter] TerrDestroy");

    for (int i = 0; i < territories; i++) {

        Territory* t = &territories[i];

        if (!t->active) continue;

        if (strcmp(t->name, name) == 0) {
            t->magic = TERR_FREE;

            t->active = false;

            t->size = 0;
            t->used = 0;
            t->next_offset = 0;

            t->start = NULL;

            terr_count--;

            ctx_push("[Exit] TerrDestroy");
            return;
        }
    }
}


int TerrCount() { // Contar territórios
    ctx_push("[Enter] TerrCount");
    unsigned char* ptr = heap;

    int total = 0;
    int active = 0;
    int inactive = 0;

    while (ptr < heap + HEAP_SIZE) {
        Territory* t = (Territory*) ptr;

        if (!t) return;
        if (t->magic != TERR_USED && t->magic != TERR_FREE) return;
        if (t->size < 0 || t->size > HEAP_SIZE) return;

        if (t->active == true) {
            active++;
        } else {
            inactive++;
        }
        ptr += sizeof(Territory);
    }

    ctx_push("[Exit] TerrCount");
    return total;
}



Territory* TerrFinder(const char* name) { // Encontrar território pelo nome
    ctx_push("[Enter] TerrFinder");

    for (int i = 0; i < territories; i++) {
        Territory* t = &territories[i];

        if (strcmp(t->name, name) == 0) {
            ctx_push("[Exit] TerrFinder");
            return t;
        }
    }

    ctx_push("[Exit] TerrFinder");
    return NULL;
}


void TerrDebug() {
    ctx_push("[Enter] TerrDebug");

    for (int i = 0; i < MAX_TERRITORIES; i++) {
        Territory* t = &territories[i];

        print("[ "), print_int(i), print(" ] "), print(t->name);
        if (t->active) {
            print("\n    Active: Yes");
            print("\n    Size: "), print_int(t->size);
            print("\n    Used: "), print_int(t->used);
        } else {
            print("\n    Size: "), print_int(t->size);
            print("\n    Active: No");
        }
    }
}