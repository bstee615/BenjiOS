#ifndef SERIAL_H
#define SERIAL_H

#include "io.h"

// Initialize the serial logging port.
void serial_init();
 
// Print a formatted string to the serial logging port in white.
void serial_printf(const char *fmt, ...);

#endif