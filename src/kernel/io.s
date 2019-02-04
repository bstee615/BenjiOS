global getc
global inb
global outb

extern term_putint

section .data

section .text

; uint8_t inb(uint16_t port)
inb:
	mov dx, [esp+4]
	xor eax, eax
	in al, dx
	ret

; void outb(uint16_t port, uint8_t val)
outb:
	push ebp
	mov ebp, esp

	push edx
	xor eax, eax

	mov eax, [ebp+12]
	mov edx, [ebp+8]
	out dx, al

	pop edx
	pop ebp
	ret

# TODO: Not tested yet.
; cu8 getc()
getc:
	mov ah, 001h ; Read key press
	int 016h ; Keyboard interrupt
	ret ; return al
