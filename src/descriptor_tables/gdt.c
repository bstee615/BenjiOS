#include "gdt.h"
#include "printf.h"

#define NUM_SEGMENTS 5
gdt_entry_t gdt[NUM_SEGMENTS];

// Set the value of one GDT entry at index i.
void gdt_set_gate(int32_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[i].base_low = (base & 0xFFFF);
    gdt[i].base_middle = (base >> 16) & 0xFF;
    gdt[i].base_high = (base >> 24) & 0xFF;

    gdt[i].limit_low = (limit & 0xFFFF);
    gdt[i].granularity = (limit >> 16) & 0x0F;

    gdt[i].granularity |= gran & 0xF0;
    gdt[i].access = access;
}

// Initialise the global descriptor table.
void init_gdt()
{
    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    gdt_ptr_t gdt_ptr;
    gdt_ptr.limit = (sizeof(gdt_entry_t) * NUM_SEGMENTS) - 1;
    gdt_ptr.base = (uint32_t)&gdt;
    gdt_flush((uint32_t)&gdt_ptr);

    printf(0, "Initialized the GDT\n");
}
