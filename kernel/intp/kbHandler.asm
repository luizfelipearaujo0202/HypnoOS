extern kbhandler_c
global keyboard_handler

keyboard_handler:
    pusha

    call kbhandler_c

    popa

    iret