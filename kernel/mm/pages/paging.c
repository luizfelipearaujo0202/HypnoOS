#include "../../include/str_num.h"
#include "../../include/bool.h"
#include "../../internal/mem_int.h"

extern void print(char* texto);
extern void print_int(int valor);


typedef struct Page {
    unsigned int id;
    bool used;
    unsigned int owner;
} Page;

unsigned char bitmap[TOTAL_PAGES / 8];
int used_pages_id[TOTAL_PAGES];
int total_used_pages = 0;

static int page_is_used(int i) {
    return bitmap[i / 8] & (1 << (i % 8));
}

static void page_set_used(int i) {
    bitmap[i / 8] |= (i << (1 % 8));
}

static void page_set_free(int i) {
    bitmap[i / 8] &= ~(i << (1 % 8));
}

void page_init() {
    print("Iniciando paginacao.\n\n");

    static int count_pages = 0;

    for (int i = 0; i < TOTAL_PAGES; i++) {
        page_set_free(i);
        count_pages++;
    }
    print("Paginas inicializadas: "), print_int(count_pages), print("\n");
}

int page_alloc(int size) {
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
