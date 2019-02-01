#if defined(__linux__)
	#error This code must be compiled with a cross-compiler
#elif !defined(__i386__)
	#error This code must be compiled with an x86-elf compiler
#endif

#include <stddef.h>
#include <stdint.h>
#include "terminal.h"
#include "pm.h"

void kmain()
{
	// Enter protected mode
	pm_init();

	term_init();

	// """"""""""user"""""""""" code
	term_print("Hello, world!\n");
	term_print("Welcome to BenjiOS.\n");
}
