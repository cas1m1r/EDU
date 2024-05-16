section .text
	global _start

_start:
	mov rdi, [rsp+16]
	mov rsi, 0
	mov rdx, 0666o
	mov rax, 2
	syscall
	
	mov eax, 3
	mov ebx, eax
	mov ecx, buf
	mov edx, bufsize
	int 0x80
	

	mov eax, 4
	mov ebx, 1
	mov ecx, buf
	mov edx, 32
	int 0x80
	
	mov eax, 1
	int 0x80


; vars
section .data
	bufsize	dw	1024

section .bss
	buf 	resb	1024

