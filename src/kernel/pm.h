#ifndef PM_H
#define PM_H

#include "descriptor_tables.h"

// Enter protected mode. IRQ and NMI should be disabled before calling.
void pm_init();

#endif