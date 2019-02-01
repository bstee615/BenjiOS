extern kmain

MB_ALIGN	equ	1 << 0
MB_MEMINFO	equ	1 << 1
MB_FLAGS	equ	MB_ALIGN | MB_MEMINFO
MB_MAGIC	equ	0x1BADB002
MB_CHECKSUM	equ	-(MB_MAGIC + MB_FLAGS)

IDT_SIZE	equ	0100h ; 32 interrupts
 
section multiboot:
align 4
	dd MB_MAGIC
	dd MB_FLAGS
	dd MB_CHECKSUM
 
section .bss:
	align 16

	; TODO: Before implementing the IDT, implement the GDT.
;	idt:
;		times 0100h db 0 ; TODO: Fill with IDT gate entries
;	idt_description:
;		dd idt
;		dw IDT_SIZE

	kstack_top:
		times 4096 db 0 ; 4Kb stack for use in  bootloader
	kstack_bottom:
 
section .text:
global start:function (start.end - start)
start:
	; Set up stack
	mov esp, kstack_bottom
	
	; Set up IDT
;	lidt [idt_description]

	; TODO: Before switching to protected mode, you must:

	; 1. Disable interrupts, including NMI (as suggested by Intel Developers Manual).
	; 2. Enable the A20 Line.
	; 3. Load the Global Descriptor Table with segment descriptors suitable for code, data, and stack. 

	; Enter kernel 
	call kmain

	; The kernel's main function should not return, but if it does then hang the CPU.
	; This approach (hlt) is more smarter (power-efficient) than the infinite loop.
	.hang:
		cli
		hlt
		jmp .hang
	.end:
