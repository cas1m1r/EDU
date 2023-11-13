#include <stdio.h>
#include <string.h>

int main(int argc, char*argv[]){
	if (argc < 2){
		printf("Usage: %s [password]\n",argv[0]);
		return -1;
	}else{
		
		printf("=== Checking Your Credentials ===\n");
		if(strcmp(argv[1],"0x53c2e7") == 0){
			printf("\t*** ACCESS GRANTED ***\n");
			return 1;
		}else{
			printf("\t~| A C C E S S  D E N I E D |~\n");
			return -1;
		}
	}
}
