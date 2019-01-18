#include <stddef.h>
#include <stdint.h>
 
#if defined(__linux__)
	#error This code must be compiled with a cross-compiler
#elif !defined(__i386__)
	#error This code must be compiled with an x86-elf compiler
#endif

int pow(int num, int exp)
{
	if (exp < 0) {
		return 0;
	}
	if (exp == 0) return 1;
	if (exp == 1) return num;

	int ret = num;
	for (; exp > 1; exp --){
		ret *= num;
	}
	return ret;
}
 
/* GDT code */
#include "gdt.h"
/* END GDT CODE*/

/* TERMINAL CODE */
volatile unsigned short* vga_buffer = (unsigned short*)0xB8000;

const int VGA_COLS = 80;
const int VGA_ROWS = 25;
 
int term_col = 0;
int term_row = 0;
unsigned char vga_color_white = 0x0F;
 
void term_init()
{
	for (int col = 0; col < VGA_COLS; col ++)
	{
		for (int row = 0; row < VGA_ROWS; row ++)
		{
			const size_t index = (VGA_COLS * row) + col;
			vga_buffer[index] = ((unsigned short)vga_color_white << 8) | ' ';
		}
	}
}

// Transpose all text in VGA buffer 1 row up and blank out the bottom row.
void term_scrolldown()
{
	for (size_t i = VGA_COLS; i < VGA_COLS * VGA_ROWS; i ++)
	{
		vga_buffer[i - VGA_COLS] = vga_buffer[i];
	}

	const int row = VGA_ROWS - 1;
	for (int col = 0; col < VGA_ROWS; col ++)
	{
		const size_t index = (VGA_COLS * row) + col;
		vga_buffer[index] = ((unsigned short)vga_color_white << 8) | ' ';
	}
}

void term_putc(char c, char color)
{
	switch (c)
	{
	case '\n':
		{
			term_col = 0;
			term_row ++;
			break;
		}
 
	default:
		{
			const size_t index = (VGA_COLS * term_row) + term_col;
			vga_buffer[index] = ((unsigned short)color << 8) | c;
			term_col ++;
			break;
		}
	}
 
	if (term_col >= VGA_COLS)
	{
		term_col = 0;
		term_row ++;
	}

	if (term_row >= VGA_ROWS)
	{
		term_scrolldown();

		term_col = 0;
		term_row = VGA_ROWS - 1;
	}
}
 
void term_print(const char* str)
{
	for (size_t i = 0; str[i] != '\0'; i ++)
	{
		term_putc(str[i], vga_color_white);
	}
}

void term_putint(int num)
{
	if (num < 0) {
		term_putc('-', vga_color_white);
		num = -num;
	}

	int num_digits = 1;
	for (int div = 10; ; div *= 10)
	{
		if (num / div == 0) break;
		else num_digits ++;
	}

	while (num_digits > 1) {
		num = num % pow(10, (num_digits));
		term_putc((num / pow(10, num_digits-1)) + '0', vga_color_white);

		num_digits --;
	}
	num = num % pow(10, (num_digits));
	term_putc(num + '0', vga_color_white);
}

void term_print_with_int(const char* str, int num)
{
	for (size_t i = 0; str[i] != '\0'; i ++)
	{
		if (str[i] == '%') {
			term_putint(num);
		}
		else {
			term_putc(str[i], vga_color_white);
		}
	}
}

/* END TERMINAL CODE */

/* TODO: Before implementing the IDT, implement the GDT.
extern void store_idt();

void print_idt_info()
{	
	unsigned int idt_address;
	unsigned short idt_size;
	store_idt();
	asm("movl %%eax, %0;"
		:"=r"(idt_address)
		:
		:"%eax");
	asm("mov %%bx, %0;"
		:"=r"(idt_size)
		:
		:"%bx");
	term_print("IDT Address="); term_putint((int)idt_address); term_print("\n");
	term_print("IDT Size="); term_putint((int)idt_size); term_print("\n");
}
*/

void kernel_main()
{
	term_init();
	gdt_init();

	term_print("Hello, world!\n");
	term_print("Welcome to BenjiOS.\n");

	// Print out information that is known to be correct.
	// term_print_with_int("Base:%\n", gdt_ptr.base);
	// term_print_with_int("Limit:%\n", gdt_ptr.limit);
	// term_print_with_int("sizeof(gdt_ptr_t):%\n", sizeof(gdt_ptr_t));
	// term_print_with_int("sizeof(gdt_segment_descriptor_t):%\n", sizeof(gdt_segment_descriptor_t));

	// Check that info about the GDT is properly stored.
	// gdt_ptr_t p;
	// store_gdt_ptr((unsigned int)(&p));
	// term_print_with_int("Stored Base:%\n", p.base);
	// term_print_with_int("Stored Limit:%\n", p.limit);
	// uint8_t *ptr_to_gdt_base = (uint8_t *)p.base;
	// for (int i = 1; i <= 4; i ++) {
	// 	term_print_with_int("===GDT segment %===\n", i);
	// 	term_print_with_int("access:%\n", ptr_to_gdt_base[8*i + 5]);
	// 	term_print_with_int("granularity:%\n", ptr_to_gdt_base[8*i + 6]);
	// }

	// TODO: Check fields in the first non-trivial segment descriptor.

	// for (int i = 0; i < VGA_ROWS - 10; i ++)
	// {
	// 	term_putc(i + 'A', vga_color_white);
	// 	term_print("Hello, World!\n");
	// }
	// term_print("Done!!\n");
}
