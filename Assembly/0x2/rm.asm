; destroy a file using commandline argument 
; remove(const char *path)

section .text
	global _start

_start:
	mov rdi, [rsp+16]	; get commandline argument of filename
	mov rax, 87			; unlink syscall
	syscall				; call kernel

	
	mov eax, 1 			; exit syscall 
	int 0x80
