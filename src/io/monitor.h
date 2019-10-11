// Defines the interface for printing to the monitor.
// From JamesM's kernel development tutorials.

#ifndef MONITOR_H
#define MONITOR_H

#include "bio.h"

// Write a single character out to the screen.
void monitor_putc(char c);

// Write a string out to the screen.
void monitor_puts(const char *s);

// Clear the screen to all black.
void monitor_cls();

#endif // MONITOR_H
