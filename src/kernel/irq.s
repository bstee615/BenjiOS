global disable_irq
global enable_irq

disable_irq:
    cli
    ret

enable_irq:
    sti
    ret