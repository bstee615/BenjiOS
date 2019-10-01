#if defined(__linux__)
	#error This code must be compiled with a cross-compiler
#elif !defined(__i386__)
	#error This code must be compiled with an x86-elf compiler
#endif

#include "stdint.h"
#include "pm.h"

#include "terminal.h"
#include "serial.h"
#include "io.h"
#include "irq.h"

// Initialize core services that require IRQ and NMI to be disabled.
void sys_init() {
	disable_irq();
	disable_nmi();

	pm_init();
	idt_init();

	enable_irq();
	enable_nmi();
}

void kmain() {
	sys_init();

	term_init();
	serial_init();

	serial_printf("%s, Benji! %d\n", "Hello", 1243);
	serial_printf("This means the serial port is working.");

	// """"""""""user"""""""""" code
	term_printf("Hello, world!\n%s version %d.", "Welcome to BenjiOS", 1);
}
