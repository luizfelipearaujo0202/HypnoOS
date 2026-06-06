#include "idt.h"
#include "io.h"
#include "../include/bool.h"
#include "../include/terminal.h"

TerminalState terminal_state = {false, 0};

struct IDTEntry idt[256];
struct IDTPointer idt_ptr;

extern void print_char(char c);
extern void print(char* texto);
extern void print_hex8(uint8_t value);

extern void idt_load(uint32_t);
extern void terminal_input(char c);

void set_idt_gate(int n, uint32_t handler) {
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector = 0x10;
    idt[n].zero = 0;
    idt[n].type_attr = 0x8E;
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

// =========== TECLADO ===========

// kernel/int/idt.c

char keyboard_map[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'ç', '\'', '`', 
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 
    0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// Variáveis de estado
static int shift_pressed = 0;

void kbhandler_c() {
    uint8_t scancode = inb(0x60);
    if (terminal_state.busy) {
        goto end;
    }
    if (!(scancode & 0x80)) {
        char c = keyboard_map[scancode];

        //print_char('{');
        //print_hex8(scancode);
        //print_char('}');

        if (c != 0) {
            print_char(c);
            terminal_input(c);
        }
    }
    
    // Shift
    if (scancode == 42 || scancode == 54) {
        shift_pressed = 1;
    }

    // ACK + EOI
    end:
        outb(0x20, 0x20);
}



void idt_init() {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;

    idt_load((uint32_t)&idt_ptr);
}