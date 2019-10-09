#include "isr.h"
#include "monitor.h"

void isr_handler(registers_t regs)
{
    monitor_write("recieved interrupt: ");
    monitor_writedecimal(regs.int_no);
    monitor_put('\n');
}
