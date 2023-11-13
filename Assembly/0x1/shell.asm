; pop a shell using execve

; define variables
section .data	
cmd 	db	'/bin/sh', 0x00
args 	dd 	cmd	   ; command
env 	dd	0h	   ; env args (empty)

section .text
	global _start

_start:
	; set up args for syscall
	mov 	edx, env
	mov 	ecx, args
	mov		ebx, cmd 

	; make the syscall 
	mov eax, 11
	int 0x80

	; exit program 
	mov eax, 1
	int 0x80


