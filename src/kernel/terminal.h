#ifndef TERMINAL_H
#define TERMINAL_H

#include "stdint.h"

// Call before any other terminal code.
void term_init();

// Print a formatted string to the terminal in white.
void term_printf(const char *fmt, ...);

#endif