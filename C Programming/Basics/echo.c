#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void usage(){
	printf("Incorrect Usage\n");
	printf("$ echo <arg>\n");
}


void main(int argc, char *argv[]){
	// check args
	if(argc < 2){
		usage();
		exit(0);
	} else {
		int i; // print the contents what user provided
		for(i = 1; i < argc; i++){
			printf("%s", argv[i]);
		}
		// add a newline at the end
		printf("\n");
	}
}