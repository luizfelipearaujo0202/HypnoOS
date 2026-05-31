#!/bin/bash

set -e

nasm -f elf32 iso/boot/boot.asm -o boot.o
nasm -f elf32 kernel/int/isr.asm -o isr_asm.o
nasm -f elf32 kernel/int/idt.asm -o idt_asm.o
nasm -f elf32 kernel/int/kbHandler.asm -o kbHandler_asm.o

gcc -m32 -ffreestanding -c kernel/int/idt.c -o idt.o
gcc -m32 -ffreestanding -c kernel/kernel.c -o kernel.o

ld -m elf_i386 -T linker.ld -o kernel.elf boot.o kernel.o idt.o idt_asm.o isr_asm.o kbHandler_asm.o 

cp kernel.elf iso/boot/

grub-mkrescue -o kernel.iso iso

qemu-system-i386 -cdrom kernel.iso

rm kernel.elf
rm kernel.o

rm idt_asm.o
rm isr_asm.o

rm kbHandler_asm.o
rm boot.o
rm kernel.o
rm idt.o

rm kernel.iso