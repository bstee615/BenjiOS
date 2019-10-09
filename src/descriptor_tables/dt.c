#include "dt.h"
#include "gdt.h"

void init_descriptor_tables()
{
    init_gdt();
}
