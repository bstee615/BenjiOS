#ifndef IRQ_H
#define IRQ_H

#include "io.h"
#include "regs.h"

extern void disable_irq();
extern void enable_irq();
extern void enable_nmi();
extern void disable_nmi();

void irq_handler(struct regs *r);
void irq_install();
void irq_install_handler(int irq, void (*handler)(struct regs *r));

#endif