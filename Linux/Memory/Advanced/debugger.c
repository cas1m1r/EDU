#include <sys/types.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/reg.h> 
#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

# define E 1337
# define CONT 852
# define SHOW 292
# define QUIT 386

/* method for creating unique indexes of items */
int hash(char key[]){
	unsigned int code = 0;
	for(int i=0; key[i] != '\0'; i++)
		code = key[i] + (code << 6) + (code << 16) - code;
	return code % E;
}

void execute(const char * p){
	 /* Allow tracing of this process */
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0){
        printf("[!] Ptrace Error\n");
    }

	execl(p, "", NULL); // call debug program with ./
}


void show_registers(int pid){
	struct user_regs_struct regs;
	ptrace(PTRACE_GETREGS, pid, 0, &regs);
	printf("RAX:\t0x%08llx\t", regs.rax);
	printf("RIP:\t0x%08llx\n", regs.rip);
	printf("RDX:\t0x%08llx\t", regs.rdx);
	printf("RDI:\t0x%08llx\n", regs.rdi);
	printf("RBP:\t0x%08llx\t", regs.rbp);
	printf("RSP:\t0x%08llx\n", regs.rsp);
	printf("SS:\t0x%08llx\t", regs.ss);
	printf("CS:\t0x%08llx\n", regs.cs);
}


void showInstructions(){
	printf("Unrecognized instruction\n");
	printf("options: [cont, show, quit]\n");
}

int main(int argc, char const *argv[]){
	if (argc < 2){
		printf("Usage: %s program\n", argv[0]);
		return -1;
	}
	bool extraArgs = false;
	const char *parg[3];
	if (argc >= 3){
		extraArgs = true;
        int numel = argc;
        printf("[-] Calling %s with %d arguments\n", argv[1], numel);
        for (int i = 2; i < argc; i ++){
            parg[i-2] = argv[i];
        }
    }


	// dont need to check if file exists, 
	// because this will be a library for python
	unsigned steps = 0; 
	const char *target = argv[1];
	
	// create second process to run the program to debug
	int pid = fork();

	if (pid == 0){ 			// Inside created process
		printf("[*] Starting %s\n", target);
		 if (!extraArgs){
            execute(target);
        }else{
            printf("Still working on this!\n");
        }
	    
	} else if (pid >=1){	// In Parent process so setup debugger
		// Get Program Registers
		show_registers(pid);
		int wait_status;
	    
	    /* Wait for child to stop on its first instruction */
	    wait(&wait_status);

	    while (WIFSTOPPED(wait_status)) {
	    	// Get the user's next action
	    	char options[256];
	        printf("[>]");
	    	scanf("%s\n", options);

	    	// hash their input to figure out which case the command falls into
	    	int selection = hash(options);
	    	switch(selection){
	    		case CONT:
	    			if (ptrace(PTRACE_SINGLESTEP, pid, 0, 0) < 0) {
			            perror("ptrace");
			            return -1;
			        }
			        break;
		        case SHOW:
		        	show_registers(pid);
		        	break;
		        case QUIT:
		        	wait(&wait_status);
		        	ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_EXITKILL);
		        	break;	
		        default:
		        	showInstructions();
		        	return 0;
	    	}
			steps++;
		}
	}
	printf("[*] Finished. [%d instructions traced]\n", steps);

	return 0;
}