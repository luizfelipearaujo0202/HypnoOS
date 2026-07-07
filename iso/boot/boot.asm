MAGIC 0x1BADB002

FLAG_VIDEO equ (1 << 2)
FLAGS equ FLAG_VIDEO

CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4

dd MAGIC
dd FLAGS
dd CHECKSUM

section .text
global start
extern HypnoOS_Main

start:
    call HypnoOS_Main

.hang:
    jmp .hang
