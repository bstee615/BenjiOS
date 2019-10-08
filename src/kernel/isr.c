#include "isr.h"
#include "serial.h"

void isr_handler(void)
{
    serial_printf("Hey!");
}