#include "idt.h"
#include "io.h"

struct IDTEntry idt[256];
struct IDTPointer idt_ptr;
void print_char(char c);

extern void idt_load(uint32_t);
extern void print(char* texto);

void set_idt_gate(int n, uint32_t handler) {
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector = 0x10;
    idt[n].zero = 0;
    idt[n].type_attr = 0x8E;
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_init() {

    outb(0x21, 0XFD);

    idt_ptr.limit = sizeof(idt) - 1;


    idt_ptr.base = (uint32_t)&idt;

    idt_load((uint32_t)&idt_ptr);

}

// =========== TECLADO ===========

char keyboard_map[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0',
    '-', '=', '\b',
    'q','w','e','r','t','y','u','i','o','p',
    '[',']','\n',
    0,  'a','s','d','f','g','h','j','k','l',
    ';','\'','`',
    0, '\\','z','x','c','v','b','n','m',
    ',', '.', '/',
};

void kbhandler_c() {
    uint8_t scancode = inb(0x60);
    print("\nExecutou handler!");

    if (scancode < 128) {
        char c = keyboard_map[c];

        if (c != 0) {
            print_char(c);
        }
    }
}