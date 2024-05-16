section .text
	global _start

_start:
	; open file
	xor rdi, rdi
	xor rcx, rcx
	mov rdi, 0x7478742e67616c66
	mov [rdx], rdi
	add al, 2
	xor rsi, rsi
	sub byte[rdx+8],0x66
	xchg rdi, rdx
	mov rdx, 0777o
	syscall
	
	; read file 
	lea rsi, [rsp]
	mov rdi, rax
	;mov dx, 27 (will still print without but extra junk too)
	xor rax, rax
	syscall
	
	; print it
	sub ax, 0x1a
	mov di, 1
	syscall
	
	; exit
	xor rax, rax
	add al, 60
	syscall
