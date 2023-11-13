; make a file using commandline argument
; open(path, O_WRONLY | O_CREAT | O_TRUNC, mod);
; O_RDONLY         00
; O_WRONLY         01
; O_RDWR           02
; O_CREAT        0100

section .text
	global _start

_start:
    mov rdi, [rsp+16]  ; get commandline argument of filename
    mov rsi, 0102o     ; O_CREAT
    mov rdx, 0666o     ; mode
    mov rax, 2         ; open file syscall
    syscall

    mov eax, 1          ; exit syscall
    int 0x80
