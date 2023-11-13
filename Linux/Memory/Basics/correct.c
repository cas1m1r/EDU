#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	// check args
	if (argc < 3){
		printf("Usage: %s width height\n", argv[0]);
		return -1;
	}
	int a, b;
	// create array based on size of input
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	
	printf("Creating [%d, %d] array\n", a, b);
	int (* dynamic)[a] = malloc(sizeof(int[a][b]));
	int i, j;
	int k = 1;
	for (i=0;i<a;i++){
		for(j=0;j<b;j++){
			dynamic[i][j] = k;
			k = k + 1;
			printf("0x%03x ", dynamic[i][j]);
		}
		printf("\n");
	}
	free(dynamic);
}