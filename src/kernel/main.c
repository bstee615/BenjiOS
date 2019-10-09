// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials

#include "monitor.h"
#include "../descriptor_tables/dt.h"

struct multiboot
{

}
__attribute__((packed));
typedef struct multiboot multiboot_t;

int main(multiboot_t *mboot_ptr)
{
    monitor_clear();
    monitor_write("Hello, world!\n");

    init_descriptor_tables();

    // All our initialisation calls will go in here.
    return 0xDEADBABA;
}