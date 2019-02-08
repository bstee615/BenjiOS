#ifndef IRQ_H
#define IRQ_H

#include "io.h"

extern void disable_irq();
extern void enable_irq();
extern void enable_nmi();
extern void disable_nmi();

#endif