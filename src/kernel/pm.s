extern gdt_init
extern flush_gdt

global pm_init

pm_init:
	cli

	call gdt_init ; Load the GDT

    ; enable protected mode
    mov eax, cr0
    or eax, 1 ; Set PE (bit 1)
    mov cr0, eax

    ; TODO: Enable the A20 line

    ; Loads  registers.
    call flush_gdt

    ; Set up a new stack
    ; TODO: find a better place for the stack.
    mov eax, [esp]
    mov esp, 0x90000
    push eax

    ret