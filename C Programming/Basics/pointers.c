#include <stdio.h>
#include <stdlib.h>

#define MAGIC 43

void populateArray(int *arr[]){
	for (int i=1;i < MAGIC; i++){
		arr[i-1] = i;
	}
}

void showArray(int *arr[]){
	for(int i=1;i <MAGIC; i++){
		printf("%d\t", arr[i-1]);
		if (i%6==0)
			printf("\n");
	}
	printf("\n");
}


void main(){
	
	// Initialize pointer
	int* ptr;

	// give pointer a value
	int value = 42;
	ptr = &value;
	printf("%d\n", *ptr);


	// Make array of pointers
	int (*nums)[MAGIC] = (int*)malloc(sizeof(int)*MAGIC);
	populateArray(nums);
	showArray(nums);
	free(nums);
}