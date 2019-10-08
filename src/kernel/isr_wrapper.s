global isr_wrapper
align 4

extern isr_handler
 
global isr_0
global isr_1
global isr_2
global isr_3
global isr_4
global isr_5
global isr_6
global isr_7
global isr_8
global isr_9
global isr_10
global isr_11
global isr_12
global isr_13
global isr_14
global isr_15
global isr_16
global isr_17
global isr_18
global isr_19
global isr_20
global isr_21
global isr_22
global isr_23
global isr_24
global isr_25
global isr_26
global isr_27
global isr_28
global isr_29
global isr_30
global isr_31

;  0: Divide By Zero Exception
isr_0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_stub

;  1: Debug Exception
isr_1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub

;  2: Non-maskable Interrupt
isr_2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub

;  3: Breakpoint
isr_3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_stub

;  4: Overflow
isr_4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_stub

;  5: Bound Range Exceeded
isr_5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_stub

;  6: Invalid Opcode
isr_6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_stub

;  7: Device Not Available
isr_7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub

;  8: Double Fault Exception (With Error Code!)
isr_8:
    cli
    push byte 8        ; Note that we DON'T push a value on the stack in this one!
                   ; It pushes one already! Use this type of stub for exceptions
                   ; that pop error codes!
    jmp isr_common_stub

;  9: Coprocessor Segment Overrun
isr_9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_stub

;  10: Invalid TSS
isr_10:
    cli
    push byte 10
    jmp isr_common_stub

;  11: Segment Not Present
isr_11:
    cli
    push byte 11
    jmp isr_common_stub

;  12: Stack-Segment Fault
isr_12:
    cli
    push byte 12
    jmp isr_common_stub

;  13: General Protection Fault
isr_13:
    cli
    push byte 13
    jmp isr_common_stub

;  14: Page Fault
isr_14:
    cli
    push byte 14
    jmp isr_common_stub

;  15: Reserved
isr_15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_stub

;  16: x87 Floating-Point Exception
isr_16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_stub

;  17: Alignment Check
isr_17:
    cli
    push byte 17
    jmp isr_common_stub

;  18: Machine Check
isr_18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_stub

;  19: SIMD Floating-Point Exception
isr_19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_stub

;  20: Virtualization Exception
isr_20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_stub

;  21: Reserved
isr_21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_stub

;  22: Reserved
isr_22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_stub

;  23: Reserved
isr_23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_stub

;  24: Reserved
isr_24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_stub

;  25: Reserved
isr_25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_stub

;  26: Reserved
isr_26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_stub

;  27: Reserved
isr_27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_stub

;  28: Reserved
isr_28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_stub

;  29: Reserved
isr_29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_stub

;  30: Security Exception
isr_30:
    cli
    push byte 30
    jmp isr_common_stub

;  31: Reserved
isr_31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub

; We call a C function in here. We need to let the assembler know
; that 'fault_handler' exists in another file
extern fault_handler

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack
    push eax
    mov eax, fault_handler
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!

isr_wrapper:
    pushad
    ; cld /* C code following the sysV ABI requires DF to be clear on function entry */
    call isr_handler
    popad
    iret