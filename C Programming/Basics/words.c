#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 512

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


void main(){
	char *alphabet[26] = {"A","B","C","D","E","F","G",
						  "H","I","J","K","L","M","N",
						  "O","P","Q","R","S","T","U",
						  "V","W","X","Y","Z"};
	int iv[5] = {7,4,11,11,14};
	for (int i=0; i < 5; i++){
		printf("%s ", alphabet[iv[i]]);
	}
	printf("\n========================\n");

	char* words[2] = {"Hello", "Friend"};
	for (int line=1; line < 10; line++){
		if(line % 2==0)
			reverse(strlen(words[0]), words[0]);
		else
			printf("%s\n", words[1]);
	}



	
}