; print to console
mov ah, 0x0e                
mov al, 'B'
int 0x10
mov al, 'o'
int 0x10
int 0x10
mov al, 't'
int 0x10
mov al, 'e'
int 0x10
mov al, 'd'
int 0x10
mov al, '.'
int 0x10
int 0x10
int 0x10

; infinite loop
loop:
    jmp loop

; padding and magic number
times 510 - ($-$$) db 0
dw 0xaa55 

; compile using: nasm -fbin boot.asm -o boot.bin
; can run using: qemu-system-x86_64 boot.bin 