section .multiboot
align 4

dd 0x1BADB002
dd 0x0
dd -(0x1BADB002 + 0x0)

section .text
global start
extern HypnoOS_Main

start:
    call HypnoOS_Main

.hang:
    jmp .hang