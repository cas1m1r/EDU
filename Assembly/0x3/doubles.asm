; doubles the value in (eax+ebx) starting from ebx
section .text
global main
extern printf

main:
	xor eax, eax
	xor ecx, ecx
	xor edx, edx
	mov eax, 1
	mov ebx, 1
	call fun

fun:
	xadd ebx, eax
	mov ecx, ebx
	cmp eax, 65536
	jg exit
	push eax
	push format
	call printf
	add esp, 8
	mov eax, ebx
	loop fun

exit:
	mov eax, 1
	int 0x80

section	.data       
	format db "%d", 10, 0

; compile with:
; nasm -f elf series.asm -o s.o && gcc -m32 s.o -o fun