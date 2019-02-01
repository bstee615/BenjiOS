global store_idt

; After this function:
;	eax == IDT_ADDR
;	bx == IDT_SIZE
store_idt:
	push ebp
	mov ebp, esp
	sub esp, 6 ; now esp == ebp - 6
	
	sidt [ebp - 6]
	mov dword eax, [ebp - 6]
	mov word bx, [ebp - 2]
	
	mov esp, ebp
	pop ebp
