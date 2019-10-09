#include "idt.h"

#define NUM_ISR 256
idt_entry_t idt[NUM_ISR];

void load_idt_entry(int index, uint32_t offset, uint16_t selector, uint8_t type_attr)
{
    idt[index].offset_lo = offset & 0x0000FFFF;
    idt[index].offset_hi = (offset & 0xFFFF0000) >> 16;

    idt[index].selector = selector;
    idt[index].type_attr = type_attr;
    idt[index].zero = 0;
}

void init_idt()
{
    // Load null entries into all slots of IDT
    for (int i = 0; i < NUM_ISR; i++)
    {
        load_idt_entry(i, 0, 0, 0);
    }

    // TODO: Load some valid entries

    idt_ptr_t idt_ptr;
    idt_ptr.size = (NUM_ISR * sizeof(idt_entry_t)) - 1;
    idt_ptr.offset = (uint32_t)&idt;
    idt_flush((uint32_t)&idt_ptr);
}
