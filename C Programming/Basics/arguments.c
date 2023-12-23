#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[]){
	// check number of arguments given
	if (argc < 2){return 15;}
	// size of first argument string
	int n = strlen(argv[1]);
	// create a local char* 
	char* argument = (char*)malloc(sizeof(char)*n);
	// copy the data from first argument string into local variable
	strncpy(argument, argv[1], n);
	// show the local variable
	printf("%s\n", argument);	
	// free the memory allocated for the local variable
	free(argument);
	// done, so leave with the size of string we looked at
	return n;
}