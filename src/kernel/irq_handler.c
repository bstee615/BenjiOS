#include "descriptor_tables.h"
#include "io.h"
#include "serial.h"
#include "terminal.h"

/* These are own ISRs that point to our special IRQ handler
*  instead of the regular 'fault_handler' function */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/* This array is actually an array of function pointers. We use
*  this to handle custom IRQ handlers for a given IRQ */
void *irq_routines[16] =
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0};

/* This installs a custom IRQ handler for the given IRQ */
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

/* This clears the handler for a given IRQ */
void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
*  is a problem in protected mode, because IDT entry 8 is a
*  Double Fault! Without remapping, every time IRQ0 fires,
*  you get a Double Fault Exception, which is NOT actually
*  what's happening. We send commands to the Programmable
*  Interrupt Controller (PICs - also called the 8259's) in
*  order to make IRQ0 to 15 be remapped to IDT entries 32 to
*  47 */
void irq_remap(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x00);
    outb(0xA1, 0x00);
}

/* We first remap the interrupt controllers, and then we install
*  the appropriate ISRs to the correct entries in the IDT. This
*  is just like installing the exception handlers */
void irq_install()
{
    irq_remap();

    set_irq_handler(32, 0x8E, 0x08, (uint32_t)irq0);
    set_irq_handler(33, 0x8E, 0x08, (uint32_t)irq1);
    set_irq_handler(34, 0x8E, 0x08, (uint32_t)irq2);
    set_irq_handler(35, 0x8E, 0x08, (uint32_t)irq3);
    set_irq_handler(36, 0x8E, 0x08, (uint32_t)irq4);
    set_irq_handler(37, 0x8E, 0x08, (uint32_t)irq5);
    set_irq_handler(38, 0x8E, 0x08, (uint32_t)irq6);
    set_irq_handler(39, 0x8E, 0x08, (uint32_t)irq7);
    set_irq_handler(40, 0x8E, 0x08, (uint32_t)irq8);
    set_irq_handler(41, 0x8E, 0x08, (uint32_t)irq9);
    set_irq_handler(42, 0x8E, 0x08, (uint32_t)irq10);
    set_irq_handler(43, 0x8E, 0x08, (uint32_t)irq11);
    set_irq_handler(44, 0x8E, 0x08, (uint32_t)irq12);
    set_irq_handler(45, 0x8E, 0x08, (uint32_t)irq13);
    set_irq_handler(46, 0x8E, 0x08, (uint32_t)irq14);
    set_irq_handler(47, 0x8E, 0x08, (uint32_t)irq15);

    serial_printf("Installed IRQs 0-15\n");
}

/* Each of the IRQ ISRs point to this function, rather than
*  the 'fault_handler' in 'isrs.c'. The IRQ Controllers need
*  to be told when you are done servicing them, so you need
*  to send them an "End of Interrupt" command (0x20). There
*  are two 8259 chips: The first exists at 0x20, the second
*  exists at 0xA0. If the second controller (an IRQ from 8 to
*  15) gets an interrupt, you need to acknowledge the
*  interrupt at BOTH controllers, otherwise, you only send
*  an EOI command to the first controller. If you don't send
*  an EOI, you won't raise any more IRQs */
void irq_handler(struct regs *r)
{
    /* This is a blank function pointer */
    void (*handler)(struct regs * r);

    /* Find out if we have a custom handler to run for this
    *  IRQ, and then finally, run it */
    handler = irq_routines[r->int_no - 32];
    term_printf("handler %d\n", (uint32_t)handler);
    if (handler)
    {
        handler(r);
    }

    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */
    if (r->int_no >= 40)
    {
        outb(0xA0, 0x20);
    }

    /* In either case, we need to send an EOI to the master
    *  interrupt controller too */
    outb(0x20, 0x20);
}