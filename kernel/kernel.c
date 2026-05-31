#include "int/idt.h"
#include "int/io.h"

extern void isr_default();

void print_char(char c);
void print(char* texto);

void HypnoOS_Main() {
    print("A");

    __asm__ volatile("cli");

    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    outb(0x21, 0x02);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0xFD); // habilita teclado
    outb(0xA1, 0xFF);

    idt_init();


    for (int i=0; i < 256; i++) {
        set_idt_gate(i, (uint32_t)isr_default);
    }
    
    print("B");
    
    __asm__ volatile("sti");
    print("HypnoOS Kernel has started.");

    while (1) {

    }
}

char* vga = (char*)0xB8000;
int cursor = 0;

void print_char(char c) {
    if (c != '\0') {
        vga[0] = c;
        vga[1] = 0x0F;
    }
}

void print(char* texto) {
    int i = 0;
    while (texto[i] != '\0') {
        vga[i * 2] = texto[i];
        vga[i * 2 + 1] = 0x0F;
        i++;
        cursor = cursor + i;
    }
}
