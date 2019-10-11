// Defines the interface for printing to the monitor.
// From JamesM's kernel development tutorials.

#ifndef MONITOR_H
#define MONITOR_H

#include "bio.h"

// Write a single character out to the screen.
void putc(char c);

// Clear the screen to all black.
void cls();

// Print a formatted string to the terminal in white.
void printf(const char *fmt, ...);

#endif // MONITOR_H
