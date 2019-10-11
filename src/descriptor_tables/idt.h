// Interrupt Descriptor Table

#ifndef IDT_H
#define IDT_H

#include "stdint.h"

// And entry for the Interrupt Descriptor Table
struct idt_entry
{
    uint16_t offset_lo; // offset bits 0..15
    uint16_t selector;  // a code segment selector in GDT or LDT
    uint8_t zero;       // unused, set to 0
    uint8_t type_attr;  // type and attributes, see https://wiki.osdev.org/IDT
    uint16_t offset_hi; // offset bits 16..31
}
__attribute__((packed));
typedef struct idt_entry idt_entry_t;

// A pointer to the IDT
struct idt_ptr
{
    uint16_t size;
    uint32_t offset;
}
__attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

// Load a reference to the location of the IDT
extern void idt_flush(uint32_t);

// Initialize the IDT
void init_idt();

#endif
