extern kbhandler_c
global keyboard_handler

keyboard_handler:
    pusha

    call kbhandler_c

    mov al, 0x20
    out 0x20, al

    popa

    iret