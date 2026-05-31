extern keyboard_c_handler
global keyboard_handler

keyboard_handler:
    pusha

    call keyboard_c_handler

    mov al, 0x20
    out 0x20, al

    popa

    iret