#include <stdio.h>


int main(int argc, char*argv[]){
	char buff[88];
	const char* s = "flag.txt";
	FILE* fd = fopen(s,"r");
	fscanf(fd, "%s\n", buff);
	fclose(fd);
	puts(buff);
	return 0;
}


//compiles to this for the const char*
