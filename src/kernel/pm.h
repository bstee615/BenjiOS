#ifndef PM_H
#define PM_H

#include "irq.h"
#include "descriptor_tables.h"

// Enter protected mode.
void pm_init();

#endif