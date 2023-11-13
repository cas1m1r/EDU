; division
section	.text
global main
extern printf     

main:
	mov edx, len
	mov ecx, msg
	mov eax, 4
	int 0x80

	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx
	mov eax, 1337
	mov ecx, 42
	div ecx

	; result is in rax
	mov ecx, eax
	push eax
	push format
	call printf
	add esp, 8
	ret 

section	.data               
	remainder db 0x0
	format db "%d", 10, 0
	msg db "1337/42 = ",0
	len equ $ - msg

; nasm -f elf div.asm && gcc -m32 -o divide div.o