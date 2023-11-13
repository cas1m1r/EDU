#include <stdio.h>
#include <string.h>

#define MAX_BUF 512

void usage(char* fname){
	printf("Usage: %s [options]\n",fname);
}

int checkLength(int N, char *str){
	if (strlen(str) > N)
		return 0;
	else
		return 1;
}


void reverse(int slen, char* argv){
	char sbuff[MAX_BUF];
	char rbuff[MAX_BUF];
	strcpy(sbuff, argv);
	int index = 0;
	for (int i = slen-1; i>=0;i--){
		rbuff[index] = sbuff[i];
		index = index + 1;
	}
	printf("%s\n",rbuff);
}

void main(int argc, char* argv[]){
	// check arguments
	if(argc < 2){
		usage(argv[0]);
		return;
	}
	
	// print argument in revese
	if (checkLength(MAX_BUF, argv[1])){
		reverse(strlen(argv[1]), argv[1]);		
	} else{
		printf(":( Mean");
	}
}