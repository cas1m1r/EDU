; trying to print fibonacci sequence
section .text
global main
extern printf

main:
	xor edx, edx
	xor ecx, ecx
	xor ebx, ebx
	xor eax, edx
	mov eax, 0
	mov ebx, 1
	mov edx, 3
	call _fib
	ret

_fib:
	; fib it up
	xadd eax, ebx
	mov edi, eax
	; loop that shit
	cmp eax, 0xe1337
	jg exit
	; show the number
	call show
	mov eax, edi
	
	jmp _fib

show:
	push eax
	push format
	call printf
	add esp, 8
	mov eax, 4
	int 0x80
	ret

exit:
	mov eax, 1
	int 0x80

section .data
	format db "%d",10,0
; nasm -f elf32 fib.asm -o fib.o && gcc -m32 fib.o -o nacci