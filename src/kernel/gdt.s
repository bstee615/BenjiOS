global load_gdt
global flush_gdt

load_gdt:
	; Move the pointer to the gdt_ptr struct into eax and load it
	mov eax, [esp+4]
	lgdt [eax]
	ret

flush_gdt:
	mov ax, 0x10 ; Move the location of the data segment into the data segment registers
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.end ; Far jump to our code segment to set cs
.end:
	ret

global store_gdt_ptr

store_gdt_ptr:
	mov eax, [esp+4]
	sgdt [eax]
	ret
