global getc

section .data

section .text

; char getc()
getc:
	mov ah, 001h ; Read key press
	int 016h ; Keyboard interrupt
	ret ; return al
