#ifndef PIC_H
#define PIC_H

#define MPIC 0x20 /* IO base address for master PIC */
#define SPIC 0xA0 /* IO base address for slave PIC */
#define MPIC_COMMAND MPIC
#define MPIC_DATA (MPIC + 1)
#define SPIC_COMMAND SPIC
#define SPIC_DATA (SPIC + 1)

#include "stdint.h"

// Send an EOI (end of interrupt) signal to the PICs.
void pic_send_eoi(uint32_t int_no);

void pic_set_irq_mask(uint8_t IRQline);
void pic_clear_irq_mask(uint8_t IRQline);

#endif