#include <string.h>


int main(int argc, char*argv[]){
	int size = strlen(argv[1]);
	char* payload[66];
	memset(payload, 0, 66);
	
	if(size>66){return 0;}
	
	strcpy(&payload, argv[1]);
	((void(*)())payload)();
	return 0;
}
