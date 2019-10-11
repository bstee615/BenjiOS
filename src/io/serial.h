// Output to serial logging port

#ifndef SERIAL_H
#define SERIAL_H

#include "bio.h"

// Initialize the serial logging port.
void serial_init();

// Put a character out to the serial logging port.
void serial_putc(char c);

// Put a string out to the serial logging port.
void serial_puts(const char *str);

#endif