#include "pic.h"
#include "bio.h"
#include "printf.h"

// Send an EOI (end of interrupt) signal to the PICs.
void pic_send_eoi(uint32_t int_no)
{
    if (int_no >= 40)
    {
        // If this interrupt involved the slave,
        // Send reset signal to slave.
        outb(SPIC, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(MPIC, 0x20);
}

void pic_set_irq_mask(uint8_t IRQline)
{
    uint16_t port;

    if (IRQline < 8)
    {
        port = MPIC_DATA;
    }
    else
    {
        port = SPIC_DATA;
        IRQline -= 8;
    }

    uint8_t value = inb(port) | (1 << IRQline);
    printf(0, "port value: %d\n", value);
    outb(port, value);
}

void pic_clear_irq_mask(unsigned char IRQline)
{
    uint16_t port;

    if (IRQline < 8)
    {
        port = MPIC_DATA;
    }
    else
    {
        port = SPIC_DATA;
        IRQline -= 8;
    }

    uint8_t value = inb(port) & ~(1 << IRQline);
    outb(port, value);
}