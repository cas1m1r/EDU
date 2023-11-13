section	.text
   global _start     
	
_start:	            ;entry point
   mov	edx,len     ;length of message
   mov	ecx,msg     ;the message being written
   mov	ebx,1       ;stdout file descriptor
   mov	eax,4       ;sys_write syscall number
   int	0x80
	
   mov	eax,1       ;sys_exit syscall number
   int	0x80 

section	.data               
msg db 'Learning Assembly is fun :D', 0xa  
len equ $ - msg              