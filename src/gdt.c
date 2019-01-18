#include "gdt.h"

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
	gdt_ptr.limit = (sizeof(gdt_segment_descriptor_t) * 5) - 1;
	gdt_ptr.base = (uint32_t) &gdt;

	// We are defining a flat memory model, where every segment can access
	//  addresses 0 to 2^32-1.
	set_gdt_segment_descriptor(0, 0, 0, 0, 0); // First entry must always be null
	set_gdt_segment_descriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel code segment
	set_gdt_segment_descriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel data segment
	set_gdt_segment_descriptor(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User code segment
	set_gdt_segment_descriptor(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User data segment

	flush_gdt((uint32_t)&gdt_ptr);
}
