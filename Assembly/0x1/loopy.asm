; For Loops with ASM

mask3	dd 0x0f

section .text
	global _start


_start:
	call		loop 		; call loop 

	; exit 
	mov		eax, 1
	int 	0x80

loop:
	mov 	edx, len1
	mov 	ecx, msg1
	mov 	ebx, 1
	mov 	eax, 4
	int 	0x80
	jmp		loop

	ret


; define variables 
section .data 
mask1	dd 0xff
mask2	dd 0xf0
msg1	db '<- Looping ->', 0xa
len1 	equ $ - msg1    