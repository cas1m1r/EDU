; prints out contents of file at a given path
section .text
	global _start

_start:
	; open the file
	mov rdi, [rsp+16]
	mov rsi, 0
	mov rdx, 0666o
	mov rax, 2
	syscall

	; read file and print line by line 
    mov     eax,  3         ; read(
    mov     ebx,  eax       ;   file_descriptor,
    mov     ecx,  buf       ;   *buf,
    mov     edx,  bufsize   ;   *bufsize)
    int     0x80            

    ; write to STDOUT
    mov     eax,  4         ; write(
    mov     ebx,  1         ;   STDOUT,
    mov     ecx,  buf       ;   *buf)
    int     0x80            
	
	; exit 
	mov eax, 1
	int 0x80

; Define Variables
section .data
   bufsize dw      1024

section .bss
   buf     resb    1024