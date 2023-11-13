/**************************************************************
* NonStandardLibC - Hooks a bunch of commonly used libc *
* functions, mostly  stdlib, to probe or reverse engineer  	  *
* how a compiledbinary might be working under the hood. 	  *
* 															  *
**************************************************************/
#define _GNU_SOURCE 
#include <sys/socket.h>
#include <termios.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <dlfcn.h>

# define LOG_FILE "hooked_nx_traffic.txt"
# define AF_INET 2

////// Declare dem hooks! (must match function signature of hook'd fcn)

int (*strcmp_actual)(char*,char*);

long unsigned int(*strlen_actual)(char*);

char* (*getenv_actual)(const char *name);

int (*setenv_actual)(char *string);

FILE* (*fopen_actual)(const char *filename, const char *mode);

int (* rand_actual) (void);

char* (* strcpy_actual)(char *dest, const char *src);

/////////////////////////////-----{ STDLIB H O O K S }-----/////////////////////////////

/* Hooks STRCMP fucntion call, prints arg strings to console */
int strcmp(char * A, char * B){
	printf("[HOOKED]==strcmp==> [%s] & [%s]\n", A, B);
	strcmp_actual = dlsym(RTLD_NEXT, "strcmp");
	return strcmp_actual(A,B);
}

/* Hooks STRLEN function call, prints the string being checked */
long unsigned int strlen(char *str){
	printf("[HOOKED]==strlen==>(%s);\n", str);
	strlen_actual = dlsym(RTLD_NEXT, "strlen");;
	return strlen_actual(str);
}


/* Hooks STRCPY and prints the string being copied */
char* strcpy(char* dst, char* src){
	printf("[HOOKED]==strcpy==>(%s, %s)\n", dst, src);
	strcpy_actual = dlsym(RTLD_NEXT, "strcpy");
	return strcpy_actual(dst, src);
}


/* Hooks GETENV function call, prints the environment variable being fetched */
char * getenv (const char *name){
	printf("[HOOKED]==getenv==>(%s)\n", name);
	getenv_actual = dlsym(RTLD_NEXT, "getenv");
	return getenv_actual(name);
}

/* Hooks SETENV function call, prints environment variable being added */
int putenv (char *string){
	printf("[HOOKED]==setenv==>(%s)\n", string);
	setenv_actual = dlsym(RTLD_NEXT, "setenv");
	return setenv_actual(string);
}

/* Hooks FOPEN function call, prints filename and mode of opening */
FILE *fopen(const char *filename, const char *mode){
	printf("[HOOKED]==fopen==>(%s, %s)\n", filename, mode);
	fopen_actual = dlsym(RTLD_NEXT, "fopen");
	return fopen_actual(filename, mode);
}


/* Hooks RAND function call, returns 42 instead of a random integer */
int rand (void){
	printf("[HOOKED]==rand==>()\n");
	rand_actual = dlsym(RTLD_NEXT, "rand");
	return 42; // :D not so random
}

/* compile with: gcc -shared  -Wl,--no-as-needed -ldl -fPIC nonstdlibc.c -o notlibc.so */
/* run using: LD_PRELOAD=notlibc.so  */
