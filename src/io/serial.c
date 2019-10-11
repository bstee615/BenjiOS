#include "serial.h"
#include "stdarg.h"
#include "math.h"

#define PORT 0x3f8 /* COM1 */

void serial_init()
{
    outb(PORT + 1, 0x00); // Disable all interrupts
    outb(PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
    outb(PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    outb(PORT + 1, 0x00); //                  (hi byte)
    outb(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
    outb(PORT + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    outb(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

int serial_received()
{
    return inb(PORT + 5) & 1;
}

char read_serial()
{
    while (serial_received() == 0)
        ;

    return inb(PORT);
}

int is_transmit_empty()
{
    return inb(PORT + 5) & 0x20;
}

void serial_putc(char a)
{
    while (is_transmit_empty() == 0)
        ;

    outb(PORT, a);
}

void write_serial_int(int num)
{
    if (num < 0)
    {
        serial_putc('-');
        num = -num;
    }

    int num_digits = 1;
    for (int div = 10;; div *= 10)
    {
        if (num / div == 0)
            break;
        else
            num_digits++;
    }

    while (num_digits > 1)
    {
        num = num % pow(10, (num_digits));
        serial_putc((num / pow(10, num_digits - 1)) + '0');

        num_digits--;
    }
    num = num % pow(10, (num_digits));
    serial_putc(num + '0');
}

void write_serial_string(const char *str)
{
    char *c;
    for (c = (char *)str; *c != 0; c++)
    {
        serial_putc(*c);
    }
}

void serial_printf(const char *fmt, ...)
{
    va_list valist;

    char *c;
    int num_fmts = 0;
    for (c = (char *)fmt; *c != 0; c++)
    {
        if (*c == '%')
            num_fmts++;
    }

    /* initialize valist for num number of arguments */
    va_start(valist, fmt);

    for (c = (char *)fmt; *c != 0; c++)
    {
        if (*c == '%')
        {
            c++; // Move c to point at the format specifier.
            switch (*c)
            {
            case 'd':
                write_serial_int(va_arg(valist, int));
                break;
            case 's':
                write_serial_string(va_arg(valist, const char *));
                break;
            }
        }
        else
        {
            serial_putc(*c);
        }
    }

    /* clean memory reserved for valist */
    va_end(valist);
}