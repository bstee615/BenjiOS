#include "isr.h"
#include "printf.h"
#include "bio.h"

#define PS2_COMMAND 0x60
#define PS2_ECHO 0xEE
#define PS2_ACK 0xFA

const char *keys = "?1234567890-=?\tqwertyuiop[]\n?asdfghjkl;'`?\\zxcvbnm,./?";

void process_scancode(uint8_t code)
{
    if (code >= 0x01 && code <= 0x36)
    {
        printf(0, "%c", keys[code - 1]);
    }
}

static void keypress_callback(registers_t regs)
{
    uint8_t b = inb(PS2_COMMAND);
    // printf(0, "COM2 Interrupt: code %d\n", b);
    process_scancode(b);
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, &keypress_callback);

    // Send to test an echo
    outb(PS2_COMMAND, 0xEE);
    uint8_t b = inb(PS2_COMMAND);
    if (b != PS2_ECHO)
    {
        printf(0, "received invalid echo %x\n", b);
    }

    // Send to enable scan codes
    outb(PS2_COMMAND, 0xF4);
    b = inb(PS2_COMMAND);
    if (b != PS2_ACK)
    {
        printf(0, "received invalid echo after interrupt %x\n", b);
    }
}