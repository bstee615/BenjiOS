#include "monitor.h"
#include "dt.h"
#include "timer.h"

struct multiboot
{

}
__attribute__((packed));
typedef struct multiboot multiboot_t;

int main(multiboot_t *mboot_ptr)
{
    cls();
    printf("Hello, world!\n");

    init_descriptor_tables();

    asm volatile("int $0x4");

    init_timer(50);
    asm volatile("sti");

    // All our initialisation calls will go in here.
    return 0xDEADBABA;
}