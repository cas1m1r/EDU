#include <stdio.h>


void showArray(int n, int arr[]){
	for(int i=0;i <= n; i++){
		printf("%d\t", arr[i]);
		if (i >0 && i%3==0)
			printf("\n");
	}
	printf("\n");
}

void buildTestArray(int n, int arr[]){
	int counter = 0;
	for(int i=0; i <=n; i++){
		counter = counter + i;
		arr[i] = counter;
	}
}

int arraySum(int n, int arr[]){
	int result = 0;
	for(int i=0;i<=n;i++){
		result = result + arr[i];
	}
	return result;
}

void arrayProduct(int m, int A[], int B[], int C[]){
	
	for(int i=0; i < m; i++){
		C[i] = A[i] * B[i];
	}
		
}


void main(void){
	int N = 9;
	int example[N];

	// fill array 
	buildTestArray(N, example);
	
	// display array 
	showArray(N, example);
	
	int sum = arraySum(N, example);
	printf("Sum of Array: %d\n", sum);

	int C[N]; arrayProduct(N, example, example, C);
	// display product
	printf("Array Squared:\n");
	showArray(N, C);

	// display sum of new array
	printf("New Array Sum:%d\n", arraySum(N, C));

}
