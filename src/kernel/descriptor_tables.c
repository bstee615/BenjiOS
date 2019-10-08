#include "descriptor_tables.h"
#include "serial.h"
#include "terminal.h"
#include "isr.h"
#include "test_irq.h"

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
	gdt_ptr.base = (uint32_t)&gdt;

	// We are defining a flat memory model, where every segment can access
	//  addresses 0 to 2^32-1.
	set_gdt_segment_descriptor(0, 0, 0, 0, 0);				  // First entry must always be null
	set_gdt_segment_descriptor(1, 0, 0x0000FFFF, 0x9A, 0xCF); // Kernel code segment
	set_gdt_segment_descriptor(2, 0, 0x0000FFFF, 0x92, 0xCF); // Kernel data segment
	set_gdt_segment_descriptor(3, 0, 0x0000FFFF, 0xFA, 0xCF); // User code segment
	set_gdt_segment_descriptor(4, 0, 0x0000FFFF, 0xF2, 0xCF); // User data segment

	load_gdt((uint32_t)&gdt_ptr);

	serial_printf("Initialized the GDT\n");
}

// Sets the offset of IRQ at index and enables it (sets bit P).
void set_irq_handler(uint8_t index, uint8_t flags, uint16_t seg, uint32_t offset)
{
	idt[index].offset_low_16 = offset & 0x0000FFFF;
	idt[index].offset_upp_16 = offset & 0xFFFF0000;
	idt[index].segment_selector = seg;
	idt[index].type_and_attr = flags;
}

/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
unsigned char *exception_messages[] =
	{
		"Divide-by-zero Error",
		"Debug",
		"Non-maskable Interrupt",
		"Breakpoint",
		"Overflow",
		"Bound Range Exceeded",
		"Invalid Opcode",
		"Device Not Available",
		"Double Fault",
		"Coprocessor Segment Overrun",
		"Invalid TSS",
		"Segment Not Present",
		"Stack-Segment Fault",
		"General Protection Fault",
		"Page Fault",
		"Reserved",
		"x87 Floating-Point Exception",
		"Alignment Check",
		"Machine Check",
		"SIMD Floating-Point Exception",
		"Virtualization Exception",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Security Exception",
		"Reserved"};

/* All of our Exception handling Interrupt Service Routines will
*  point to this function. This will tell us what exception has
*  happened! Right now, we simply halt the system by hitting an
*  endless loop. All ISRs disable interrupts while they are being
*  serviced as a 'locking' mechanism to prevent an IRQ from
*  happening and messing up kernel data structures */
void fault_handler(struct regs *r)
{
	/* Is this a fault whose number is from 0 to 31? */
	if (r->int_no < 32)
	{
		/* Display the description for the Exception that occurred.
        *  In this tutorial, we will simply halt the system using an
        *  infinite loop */
		serial_printf(exception_messages[r->int_no]);
		serial_printf(" Exception. System Halted!\n");
		for (;;)
			;
	}
}

extern void isr_0();
extern void isr_1();
extern void isr_2();
extern void isr_3();
extern void isr_4();
extern void isr_5();
extern void isr_6();
extern void isr_7();
extern void isr_8();
extern void isr_9();
extern void isr_10();
extern void isr_11();
extern void isr_12();
extern void isr_13();
extern void isr_14();
extern void isr_15();
extern void isr_16();
extern void isr_17();
extern void isr_18();
extern void isr_19();
extern void isr_20();
extern void isr_21();
extern void isr_22();
extern void isr_23();
extern void isr_24();
extern void isr_25();
extern void isr_26();
extern void isr_27();
extern void isr_28();
extern void isr_29();
extern void isr_30();
extern void isr_31();

void enable_some_irq_handlers()
{
	set_irq_handler(0x00, 0x8E, 0x08, (uint32_t)isr_0);
	set_irq_handler(0x01, 0x8E, 0x08, (uint32_t)isr_1);
	set_irq_handler(0x02, 0x8E, 0x08, (uint32_t)isr_2);
	set_irq_handler(0x03, 0x8E, 0x08, (uint32_t)isr_3);
	set_irq_handler(0x04, 0x8E, 0x08, (uint32_t)isr_4);
	set_irq_handler(0x05, 0x8E, 0x08, (uint32_t)isr_5);
	set_irq_handler(0x06, 0x8E, 0x08, (uint32_t)isr_6);
	set_irq_handler(0x07, 0x8E, 0x08, (uint32_t)isr_7);
	set_irq_handler(0x08, 0x8E, 0x08, (uint32_t)isr_8);
	set_irq_handler(0x09, 0x8E, 0x08, (uint32_t)isr_9);
	set_irq_handler(0x0A, 0x8E, 0x08, (uint32_t)isr_10);
	set_irq_handler(0x0B, 0x8E, 0x08, (uint32_t)isr_11);
	set_irq_handler(0x0C, 0x8E, 0x08, (uint32_t)isr_12);
	set_irq_handler(0x0D, 0x8E, 0x08, (uint32_t)isr_13);
	set_irq_handler(0x0E, 0x8E, 0x08, (uint32_t)isr_14);
	set_irq_handler(0x0F, 0x8E, 0x08, (uint32_t)isr_15);
	set_irq_handler(0x10, 0x8E, 0x08, (uint32_t)isr_16);
	set_irq_handler(0x11, 0x8E, 0x08, (uint32_t)isr_17);
	set_irq_handler(0x12, 0x8E, 0x08, (uint32_t)isr_18);
	set_irq_handler(0x13, 0x8E, 0x08, (uint32_t)isr_19);
	set_irq_handler(0x14, 0x8E, 0x08, (uint32_t)isr_20);
	set_irq_handler(0x15, 0x8E, 0x08, (uint32_t)isr_21);
	set_irq_handler(0x16, 0x8E, 0x08, (uint32_t)isr_22);
	set_irq_handler(0x17, 0x8E, 0x08, (uint32_t)isr_23);
	set_irq_handler(0x18, 0x8E, 0x08, (uint32_t)isr_24);
	set_irq_handler(0x19, 0x8E, 0x08, (uint32_t)isr_25);
	set_irq_handler(0x1A, 0x8E, 0x08, (uint32_t)isr_26);
	set_irq_handler(0x1B, 0x8E, 0x08, (uint32_t)isr_27);
	set_irq_handler(0x1C, 0x8E, 0x08, (uint32_t)isr_28);
	set_irq_handler(0x1D, 0x8E, 0x08, (uint32_t)isr_29);
	set_irq_handler(0x1E, 0x8E, 0x08, (uint32_t)isr_30);
	set_irq_handler(0x1F, 0x8E, 0x08, (uint32_t)isr_31);
}

void idt_init()
{
	idt_ptr.limit = (sizeof(idt_descriptor_t) * NUM_IRQS) - 1;
	idt_ptr.base = (uint32_t)&idt;

	// Set all IRQs with these settings for attr:
	// - P 0 (Unused)
	// - DPL 3 (User code)
	// - S 0 (Interrupt/trap gate)
	// ...and type = interrupt gate.
	// Segment is 0x8, Kernel Code, and Offset is not touched.
	// For traps, set Gate Type (low 4 bits of type_and_attr) to 0xF.
	// When enabling an IRQ, set_irq_handler() enables P and sets the offset.
	for (int i = 0; i < NUM_IRQS; i++)
	{
		idt[i].segment_selector = 0x08;
		idt[i].type_and_attr = 0x6E;
	}

	enable_some_irq_handlers();

	load_idt((uint32_t)&idt_ptr);

	test_irq();

	serial_printf("Initialized the IDT\n");
}
