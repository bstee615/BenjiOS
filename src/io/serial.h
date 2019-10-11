// Output to serial logging port

#ifndef SERIAL_H
#define SERIAL_H

#include "io.h"

// Initialize the serial logging port.
void serial_init();

// Put a character out to the serial logging port.
void serial_putc(char c);

// Print a formatted string to the serial logging port in white.
void serial_printf(const char *fmt, ...);

#endif