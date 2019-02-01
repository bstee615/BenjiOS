#include "terminal.h"
#include "math.h"

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

const int VGA_COLS = 80;
const int VGA_ROWS = 25;
 
int term_col = 0;
int term_row = 0;
unsigned char vga_color_white = 0x0F;

// Internal method
// Transpose all text in VGA buffer 1 row up and blank out the bottom row.
void term_scrolldown()
{
	for (unsigned int i = VGA_COLS; i < VGA_COLS * VGA_ROWS; i ++)
	{
		vga_buffer[i - VGA_COLS] = vga_buffer[i];
	}

	const int row = VGA_ROWS - 1;
	for (int col = 0; col < VGA_ROWS; col ++)
	{
		const unsigned int index = (VGA_COLS * row) + col;
		vga_buffer[index] = ((unsigned short)vga_color_white << 8) | ' ';
	}
}

// Internal method
// Print one character to terminal with color.
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
			const unsigned int index = (VGA_COLS * term_row) + term_col;
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

void term_init()
{
	for (int col = 0; col < VGA_COLS; col ++)
	{
		for (int row = 0; row < VGA_ROWS; row ++)
		{
			const unsigned int index = (VGA_COLS * row) + col;
			vga_buffer[index] = ((unsigned short)vga_color_white << 8) | ' ';
		}
	}
}

void term_print(const char* str)
{
	for (unsigned int i = 0; str[i] != '\0'; i ++)
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
	for (unsigned int i = 0; str[i] != '\0'; i ++)
	{
		if (str[i] == '%') {
			term_putint(num);
		}
		else {
			term_putc(str[i], vga_color_white);
		}
	}
}