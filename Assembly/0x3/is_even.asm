; check if number is even
section .text
global main
extern printf


main:
	; display first number with printf
	mov ecx, A
	mov edx, 4
	mov ebx, 1
	mov eax, 4
	int 0x80

	; clear out registers
	xor eax, eax
	xor ecx, ecx
	xor edx, edx

	; check if A is even
	mov eax, 1337
	mov ecx, 2
	div ecx

	; remainder in edx
	mov eax, edx
	cmp eax, 0
	je isEven
	call isOdd
	
	; display B
	mov ecx, B
	mov edx, 4
	mov ebx, 1
	mov eax, 4
	int 0x80

	; clear out registers
	xor eax, eax
	xor ecx, ecx
	xor edx, edx

	; check if B is even
	mov eax, 42
	mov ecx, 2
	div ecx

	; remainder in edx
	mov eax, edx
	cmp eax, 0
	je isEven
	call isOdd

	; exit 
	mov eax, 1
	int 0x80

	

	isEven:
		; number is even
		push eax
		push format
		call printf
		add esp, 8
		mov edx, evenlen
		mov ecx, emsg
		mov eax, 4
		int 0x80

		; exit 
		mov eax, 1
		int 0x80

	isOdd:
		; number is odd
		push eax
		push format
		call printf
		add esp, 8
		mov edx, oddlen
		mov ecx, omsg
		mov eax, 4
		int 0x80

		


section .data
	format db "%d",0
	omsg db " is odd",10,0
	oddlen equ $ - omsg
	emsg db " is even",10,0
	evenlen equ $ - emsg
	A db "1337",0
	B db "42", 0

; compile with:
; nasm -f elf odd\|\|even.asm -o oddoreven.o && gcc -m32 oddoreven.o -o isItOdd
