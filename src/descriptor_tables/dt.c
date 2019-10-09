#include "dt.h"
#include "gdt.h"
#include "idt.h"

void init_descriptor_tables()
{
    init_gdt();
    init_idt();
}
