#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
 
// Call before any other terminal code.
void term_init();
 
// Print str in white.
void term_print(const char* str);

// Print int in decimal.
void term_putint(int num);

// Interpolate num with str and print in white.
void term_print_with_int(const char* str, int num);

#endif