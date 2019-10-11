#include "printf.h"
#include "stdarg.h"
#include "monitor.h"
#include "serial.h"

typedef void (*putc_cb)(char c);
typedef void (*puts_cb)(const char *c);

void putint(putc_cb putc, int n)
{
    int negative = 0;
    if (n < 0)
    {
        negative = 1;
        n = -n;
    }
    int last_digit_0 = (n % 10 == 0) ? 1 : 0;

    int r = 0;
    while (n > 0)
    {
        r *= 10;
        r += n % 10;
        n /= 10;
    }

    if (negative)
    {
        putc('-');
    }
    while (r > 0)
    {
        putc('0' + r % 10);
        r /= 10;
    }
    if (last_digit_0)
    {
        putc('0');
    }
}

void putint_hex(putc_cb putc, int n)
{
    int negative = 0;
    if (n < 0)
    {
        negative = 1;
        n = -n;
    }
    int last_digit_0 = (n % 16 == 0) ? 1 : 0;

    if (negative)
    {
        putc('-');
    }
    putc('0');
    putc('x');
    int r = 0;
    while (n > 0)
    {
        r = r * 16;
        r += n % 16;
        n /= 16;
    }

    while (r > 0)
    {
        int digit = r % 16;
        if (digit > 9)
        {
            putc('A' + digit - 10);
        }
        else
        {
            putc('0' + digit);
        }
        r /= 16;
    }
    if (last_digit_0)
    {
        putc('0');
    }
}

void generic_printf(putc_cb putc, puts_cb puts, const char *fmt, va_list valist)
{
    for (char *c = (char *)fmt; *c != 0; c++)
    {
        if (*c == '%')
        {
            c++; // Move c to point at the format specifier.
            switch (*c)
            {
            case 'd':
                putint(putc, va_arg(valist, int));
                break;
            case 'x':
                putint_hex(putc, va_arg(valist, int));
                break;
            case 's':
                puts(va_arg(valist, char *));
                break;
            }
        }
        else
        {
            putc(*c);
        }
    }
}

void printf(int method, const char *fmt, ...)
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

    putc_cb putc;
    puts_cb puts;

    if (method == 0)
    {
        putc = monitor_putc;
        puts = monitor_puts;
    }
    if (method == 1)
    {
        putc = serial_putc;
        puts = serial_puts;
    }

    generic_printf(putc, puts, fmt, valist);

    /* clean memory reserved for valist */
    va_end(valist);
}
