#ifndef GDT_H
#define GDT_H

#include <stdint.h>

struct gdt_segment_descriptor_t
{
	uint16_t limit_low_16;
	uint16_t base_low_16;

	uint8_t base_mid_8;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_upp_8;
} __attribute__ ((packed)); 
typedef struct gdt_segment_descriptor_t gdt_segment_descriptor_t; 

// Special pointer to the GDT
struct gdt_ptr_t
{
	uint16_t limit; // The size of the GDT in bytes
	uint32_t base; // The address of the first GDT entry
} __attribute__ ((packed));
typedef struct gdt_ptr_t gdt_ptr_t;

// Actual array of segment descriptors
#define GDT_SIZE 5
gdt_ptr_t gdt_ptr;
gdt_segment_descriptor_t gdt[GDT_SIZE];

// Defined in ASM
extern void flush_gdt(unsigned int gdt_ptr_address);
extern void store_gdt_ptr(unsigned int gdt_ptr_address);

void gdt_init();

#endif