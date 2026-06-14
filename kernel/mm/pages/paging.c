#include "../../include/str_num.h"
#include "../../include/bool.h"


#define HEAP_SIZE (4096 * 4096)
#define PAGE_SIZE 1024
#define TOTAL_PAGES (HEAP_SIZE / PAGE_SIZE)

extern void print(char* texto);
extern void print_int(int valor);


static unsigned char heap[HEAP_SIZE];


typedef struct Page {
    unsigned int id;
    bool used;
    unsigned int owner;
} Page;

static int count_pages = 0;

unsigned char bitmap[TOTAL_PAGES / 8];
int used_pages_id[TOTAL_PAGES];
int total_used_pages = 0;

static int page_is_used(int i) {
    return bitmap[i / 8] & (i << (i % 8));
}

static void page_set_used(int i) {
    bitmap[i / 8] |= (i << (i % 8));
}

static void page_set_free(int i) {
    bitmap[i / 8] &= ~(i << (i % 8));
}

void page_init() {
    print("Iniciando paginacao.\n\n");

    for (int i = 0; i < TOTAL_PAGES; i++) {
        page_set_free(i);
        count_pages++;
    }
    print("Paginas inicializadas: "), print_int(count_pages), print("\n");
}

int page_alloc(size) {
    int next_number = 1;
    int pages[TOTAL_PAGES];

    for (int i = 0; i < TOTAL_PAGES; i++) {
        if (!page_is_used(i)) {
            page_set_used(i);

            pages[next_number] = i;
            next_number++;

            total_used_pages++;
            used_pages_id[TOTAL_PAGES] = i;
        }
        return pages;
    }
    return -1; // sem memória
}
