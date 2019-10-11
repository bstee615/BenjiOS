#include "isr.h"
#include "printf.h"
#include "bio.h"
#include "pic.h"

void isr_handler(registers_t regs)
{
    printf(0, "recieved interrupt: %d\n", regs.int_no);
}

isr_t irqs[256];

void irq_handler(registers_t regs)
{
    pic_send_eoi(regs.int_no);

    if (irqs[regs.int_no] != 0)
    {
        isr_t handler = irqs[regs.int_no];
        handler(regs);
    }
    else
    {
        printf(0, "unregistered interrupt occured: %d\n", regs.int_no);
    }
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    irqs[n] = handler;
}
