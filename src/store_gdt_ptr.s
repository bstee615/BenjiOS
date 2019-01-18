global store_gdt_ptr

store_gdt_ptr:
	mov eax, [esp+4]
	sgdt [eax]
	ret
