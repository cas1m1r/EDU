section .text
	global _start

_start:
	xor rdi, rdi
	xor rcx, rcx
	mov rdi, 0x0a6e5c4f
	shl rdi, 32
	add rdi, 0x4c4c4548
	mov [rsi], rdi
	sub byte[rsi+9],0x0a
	mov rdx, 5
	mov rax, 1
	mov rdi, 1
	syscall
	
	xor rax, rax
	add al, 60
	syscall
