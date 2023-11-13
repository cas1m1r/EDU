section	.text
   global _start        ;must be declared for using gcc
	
_start:	                ;tell linker entry point
   call    display
   call    exit
	
display:
   mov    ecx, 256
	
next:
   mov     eax, 4
   mov     ebx, 1
   mov     ecx, achar
   mov     edx, 1
   int     0x80
	
   mov	dx, [achar]
   cmp	dx, 0x7e 
   jg   exit
   inc	byte [achar]
   loop    next
   ret

exit:
   mov  eax,1
   int  0x80

	
section .data
achar db '0'
