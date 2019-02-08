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

void kmain()
{
	// Enter protected mode
	pm_init();

	term_init();

	serial_init();

	serial_printf("%s, Benji! %d", "Hello", 1243);

	// """"""""""user"""""""""" code
	term_printf("Hello, world!\n%s version %d.", "Welcome to BenjiOS", 1);
}
