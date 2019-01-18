#include "gdt.h"
#include <stdio.h>

#define SEGMENT_TYPE_CODE 0xA
#define SEGMENT_TYPE_DATA 0x2

#define ACCESS_FLAGS_KERNEL 0x9
#define ACCESS_FLAGS_USER 0xF

void set_gdt_segment_descriptor(int idx, unsigned int base, unsigned int limit, unsigned char gran, unsigned char access_flags, unsigned char segment_type);

int main() {
	// set_gdt_segment_descriptor(0, 0, 0, 0, 0, 0); // First entry must always be null
	set_gdt_segment_descriptor(1, 0, 0xFFFFFFFF, 0xC,
		ACCESS_FLAGS_KERNEL, SEGMENT_TYPE_CODE); // Kernel code segment
    int idx = 1;
    gdt_segment_descriptor_t seg = gdt[idx];
    unsigned int base = 0;
    base |= seg.base_low_16;
    base |= seg.base_mid_8 << 16;
    base |= seg.base_upp_8 << 24;
    printf("Base: 0x%x\n", base);
    unsigned int lim = 0;
    lim |= seg.limit_low_16;
    lim |= (seg.granularity & 0x0F) << 16;
    printf("Limit: 0x%x\n", lim);
    unsigned char gran = 0;
    gran |= (seg.granularity & 0xF0) >> 4;
    printf("Granularity flags: 0x%x\n", gran);
    unsigned char access = 0;
    access |= seg.access & 0x0F;
    printf("Access flags: 0x%x\n", access);
    unsigned char type = 0;
    type |= (seg.access & 0xF0) >> 4;
    printf("Type flags: 0x%x\n", type);

// 	set_gdt_segment_descriptor(2, 0, 0xFFFFFFFF, 0xC,
// 		ACCESS_FLAGS_KERNEL, SEGMENT_TYPE_DATA); // Kernel data segment
// 	set_gdt_segment_descriptor(3, 0, 0xFFFFFFFF, 0xC,
// 		ACCESS_FLAGS_USER, SEGMENT_TYPE_CODE); // User code segment
// 	set_gdt_segment_descriptor(4, 0, 0xFFFFFFFF, 0xC,
// 		ACCESS_FLAGS_USER, SEGMENT_TYPE_DATA); // User data segment
}