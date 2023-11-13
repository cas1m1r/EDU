#!/bin/bash
echo '[+] Cleaning Old Build'
rm *.o
rm kernel
rm -rf iso

echo '[+] Building OS'
nasm -f elf32 boot.asm -o boot.o
gcc -m32 -c kernel.c -o kernel.o
gcc -m32 -c keyboard.c -o Keyboard.o
gcc -m32 -c source.c -o Source.o
ld -m elf_i386 -T linker.ld -o kernel boot.o kernel.o Keyboard.o Source.o
mkdir -p iso/boot/grub
cp kernel iso/boot/
cp grub.cfg iso/boot/grub/
grub-mkrescue -o my-kernel.iso iso/
#EOF