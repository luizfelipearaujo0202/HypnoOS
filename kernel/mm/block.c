typedef struct Block {
    unsigned int size;
    unsigned char free;
} Block;

#define HEAP_SIZE (1024 * 1024)

extern void print(char* texto);
extern void print_int(int valor);


void heap_debug();

static unsigned char heap[HEAP_SIZE];
static unsigned int heap_end = 0;

void* kmalloc(unsigned int size) {
    unsigned char* ptr = heap;

    while (ptr < heap + heap_end) {
        Block* block = (Block*) ptr;

        if (block->free == 1 && block->size >= size) {
            block-> free = 0;
            return ptr + sizeof(Block);
        }

        ptr = ptr + sizeof(Block) + block->size;

        if (heap_end + sizeof(Block) + size > HEAP_SIZE) return 0;
    }

    Block* new_block = (Block*) (heap + heap_end);

    new_block->size = size;
    new_block->free = 0;

    void* data = heap + heap_end + sizeof(Block);

    heap_end += sizeof(Block) + size;

    heap_debug();
    return data;
    
}

void heap_debug() {
    unsigned char* ptr = heap;

    print("\n=== HEAP DEBUG ===\n");

    while (ptr < heap + heap_end) {
        Block* block = (Block*) ptr;

        if (block->free)
            print("[FREE ");
        else
            print("[USED ");
        
        print("size="), print_int(block->size), print("]");

    ptr = ptr + sizeof(Block) + block->size;

    print("\n=======================\n");
    }
}