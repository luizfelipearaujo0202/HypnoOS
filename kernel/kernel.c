#include "include/bool.h"
#include "include/terminal.h"
#include "intp/idt.h"
#include "intp/io.h"

extern void isr_default();
extern void keyboard_handler();

extern char* terminal_readline(char* prompt);

extern void* kmalloc(unsigned int size);

void print_char(char c);
void print(char* texto);

void HypnoOS_Main(uint32_t multiboot_info) {
    outb(0x20, 0x20);

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


    for (int i=0; i < 256; i++) {
        set_idt_gate(i, (uint32_t)isr_default);
    }
    
    set_idt_gate(33, (uint32_t)keyboard_handler);

    idt_init();

    // ======= VARIÁVEIS =======

    __asm__ volatile("sti");

    print("HypnoOS Kernel has started.\n");
    print("---------------------------");
    print_char('\n');

    while (1) {
        // kmalloc(5);
        terminal_readline("\n\nHypnoOS >> ");
        terminal_state.busy = false;
        __asm__ volatile("hlt");
    }
}

static uint16_t* vga = (uint16_t*)0xB8000;
static int cursor_x = 0;
static int cursor_y = 0;

static void move_cursor(int x, int y) {
    uint16_t pos = y * 80 + x;

    __asm__ volatile ("outb %0, %1" : : "a"((uint8_t)(pos & 0xFF)), "Nd"(0x3D5));
    __asm__ volatile ("outb %0, %1" : : "a"((uint8_t)(pos >> 8)), "Nd"(0x3D5));
}

static void scroll() {
    if (cursor_y < 25) {
        return;
    }

    for (int y = 1; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            vga[(y-1) * 80 + x] = vga[y * 80 + x];
        }
    }

    for (int x = 0; x < 25; x++) {
        vga[(25 - 1) * 80 + x] = (0x0F << 8) | ' ';
    }

    cursor_y = 25 - 1;
}

void print_char(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    }

    else if (c == '\b') {
        if (cursor_x > 0) {
            cursor_x--;
            vga[cursor_y * 80 + cursor_x] = (0x0F << 8) | ' ';
        }
    }
    else if (c == '\n') {
        print("ENTER");
    }

    else if (c < 32) {
        return;
    }

    else {
        vga[cursor_y * 80 + cursor_x] = (0x0F << 8) | c;
        cursor_x++;
    }


    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }

    scroll();
    move_cursor(cursor_x, cursor_y);
}

void print_hex8(uint8_t value) {
    char hex[] = "0123456789ABCDEF";

    print_char(hex[value >> 4]);
    print_char(hex[value & 0x0F]);
}

void print(char* texto) {
    int i = 0;

    while (texto[i] != '\0') {
        print_char(texto[i]);
        i++;
    }
}