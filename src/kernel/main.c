#include "monitor.h"
#include "printf.h"
#include "dt.h"
#include "timer.h"
#include "pic.h"

struct multiboot
{

}
__attribute__((packed));
typedef struct multiboot multiboot_t;

int main(multiboot_t *mboot_ptr)
{
    monitor_cls();
    printf(0, "Hello, world!\n");

    init_descriptor_tables();

    asm volatile("int $0x4");

    pic_clear_irq_mask(1);

    printf(0, "Decimal %d\nHex %x\n", 36, 36);
    printf(0, "Zero %d\nZero in ones digit %d\nZero in ones digit hex %x\nNegative %d\n", 0, 40, 0x30, -3);

    init_timer(50);
    asm volatile("sti");

    // All our initialisation calls will go in here.
    return 0xDEADBABA;
}