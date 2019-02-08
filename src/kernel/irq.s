global disable_irq
global enable_irq
global disable_nmi
global enable_nmi

extern inb
extern outb

disable_irq:
    cli
    ret

enable_irq:
    sti
    ret

; outb(0x70, inb(0x70) & 0x7F);
enable_nmi:
    ; inb(0x70)
    push 0x70
    call inb
    add esp, 4

    ; eax = inb(0x70) & 0x7F
    and eax, 0x7F

    ; outb(0x70, eax)
    push eax
    push 0x70
    call outb
    add esp, 8

    ret

; outb(0x70, inb(0x70) | 0x80);
disable_nmi:
    ; inb(0x70)
    push 0x70
    call inb
    add esp, 4

    ; eax = inb(0x70) | 0x80
    or eax, 0x80

    ; outb(0x70, eax)
    push eax
    push 0x70
    call outb
    add esp, 8

    ret