#include "idt.h"
#include "printf.h"
#include "isr.h"
#include "bio.h"

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

void remap_irqs()
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void init_idt()
{
    // Load null entries into all slots of IDT
    for (int i = 0; i < NUM_ISR; i++)
    {
        load_idt_entry(i, 0, 0, 0);
    }

    remap_irqs();

    // TODO: Load some valid entries
    load_idt_entry(4, (uint32_t)isr4, 0x08, 0x8E);

    load_idt_entry(32, (uint32_t)irq0, 0x08, 0x8E);
    load_idt_entry(33, (uint32_t)irq1, 0x08, 0x8E);
    load_idt_entry(34, (uint32_t)irq2, 0x08, 0x8E);
    load_idt_entry(35, (uint32_t)irq3, 0x08, 0x8E);
    load_idt_entry(36, (uint32_t)irq4, 0x08, 0x8E);
    load_idt_entry(37, (uint32_t)irq5, 0x08, 0x8E);
    load_idt_entry(38, (uint32_t)irq6, 0x08, 0x8E);
    load_idt_entry(39, (uint32_t)irq7, 0x08, 0x8E);
    load_idt_entry(40, (uint32_t)irq8, 0x08, 0x8E);
    load_idt_entry(41, (uint32_t)irq9, 0x08, 0x8E);
    load_idt_entry(42, (uint32_t)irq10, 0x08, 0x8E);
    load_idt_entry(43, (uint32_t)irq11, 0x08, 0x8E);
    load_idt_entry(44, (uint32_t)irq12, 0x08, 0x8E);
    load_idt_entry(45, (uint32_t)irq13, 0x08, 0x8E);
    load_idt_entry(46, (uint32_t)irq14, 0x08, 0x8E);
    load_idt_entry(47, (uint32_t)irq15, 0x08, 0x8E);

    idt_ptr_t idt_ptr;
    idt_ptr.size = (NUM_ISR * sizeof(idt_entry_t)) - 1;
    idt_ptr.offset = (uint32_t)&idt;
    idt_flush((uint32_t)&idt_ptr);

    printf(0, "Initialized the IDT\n");
}
