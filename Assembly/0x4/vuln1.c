#include <string.h>
#include <unistd.h>

int main(int argc, char*argv[]){
	char* code[250];
	memset(code, 0, 250);
	
	int nread = read(0, code, 250);
	((void(*)())code)();
	return 0;
}
