// Defines the interface for PIT interrupt harness.
// Written for JamesM's kernel development tutorials.

#ifndef TIMER_H
#define TIMER_H

#include "bio.h"

// Initialize the timer to a certain
void init_timer(uint32_t frequency);

#endif