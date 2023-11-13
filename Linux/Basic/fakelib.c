#define _GNU_SOURCE 
#include <sys/socket.h>
#include <stdint.h>
#include <stdio.h>
#include <dlfcn.h>

int strcmp(char * A, char * B){
	printf("Hooked: strcmp(%s,\t%s)\n",A,B);
	int (*real_strcmp)(char*,char*) = NULL;
	real_strcmp = dlsym(RTLD_NEXT, "strcmp");
	return 0;
}

/* compile with: gcc -shared  -Wl,--no-as-needed -ldl -fPIC fakelib.c -o hook.so */
/* run using: LD_PRELOAD=hook.so  */
// 