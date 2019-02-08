global test_irq
global dummy_irq

extern serial_putc

test_irq:
    int 0x50
    ret

dummy_irq:
    push 0x40
    call serial_putc
    add esp, 4
    iret