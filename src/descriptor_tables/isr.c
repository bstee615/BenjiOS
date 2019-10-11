#include "isr.h"
#include "../io/monitor.h"

void isr_handler(registers_t regs)
{
    printf("recieved interrupt: %d\n", regs.int_no);
}

isr_t irqs[256];

void irq_handler(registers_t regs)
{
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs.int_no >= 40)
    {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(0x20, 0x20);

    if (irqs[regs.int_no] != 0)
    {
        isr_t handler = irqs[regs.int_no];
        handler(regs);
    }
    else
    {
        printf("unregistered interrupt occured: %d\n", regs.int_no);
    }
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    irqs[n] = handler;
}
