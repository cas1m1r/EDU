; multiplication 
section	.text
global main
extern printf     

main:
	xor eax, eax
	xor edx, edx
	mov eax, 42
	mov ecx, 1337
	mul ecx

	; result is in rax
	push eax
	push format
	call printf
	add esp, 8
	ret

section	.data               
format db "%d", 10, 0