#include "descriptor_tables.h"

//Internal method
void set_gdt_segment_descriptor(int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt[idx].base_low_16 = base & 0xFFFF;
	gdt[idx].base_mid_8 = (base >> 16) & 0xFF;
	gdt[idx].base_upp_8 = (base >> 24) & 0xFF;

	gdt[idx].limit_low_16 = limit & 0xFFFF;

	gdt[idx].granularity = ((limit >> 16) & 0x0F) |
							(gran << 4 & 0xF0);
	gdt[idx].access = access;
}

void gdt_init()
{
	gdt_ptr.limit = (sizeof(gdt_segment_descriptor_t) * GDT_SIZE) - 1;
	gdt_ptr.base = (uint32_t) &gdt;

	// We are defining a flat memory model, where every segment can access
	//  addresses 0 to 2^32-1.
	set_gdt_segment_descriptor(0, 0, 0, 0, 0); // First entry must always be null
	set_gdt_segment_descriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel code segment
	set_gdt_segment_descriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel data segment
	set_gdt_segment_descriptor(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User code segment
	set_gdt_segment_descriptor(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User data segment

	load_gdt((uint32_t)&gdt_ptr);
}

// Sets the offset of IRQ at index and enables it (sets bit P).
void set_irq_handler(uint8_t index, uint32_t offset)
{
	idt[index].offset_low_16 = offset & 0x0000FFFF;
	idt[index].offset_upp_16 = offset & 0xFFFF0000;
	idt[index].type_and_attr = idt[index].type_and_attr | 0x80;
}

void idt_init()
{
	idt_ptr.limit = (sizeof(idt_descriptor_t) * NUM_IRQS) - 1;
	idt_ptr.base = (uint32_t) &idt;

	// Set all IRQs with these settings for attr:
	// - P 0 (Unused)
	// - DPL 3 (User code)
	// - S 0 (Interrupt/trap gate)
	// ...and type = interrupt gate.
	// Segment is 0x8, Kernel Code, and Offset is not touched.
	// For traps, set Gate Type (low 4 bits of type_and_attr) to 0xF.
	// When enabling an IRQ, set_irq_handler() enables P and sets the offset.
	for (int i = 0; i < NUM_IRQS; i ++) {
		idt[i].segment_selector = 0x08;
		idt[i].type_and_attr = 0x6E;
	}

	load_idt((uint32_t)&idt_ptr);
}
