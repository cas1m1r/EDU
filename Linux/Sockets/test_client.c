#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
	// check args for the remote address and port to connect to
	if (argc <3 ){
		printf("Usage: %s [ip] [port]\n", argv[0]);
		return -1;
	}
	int retval;
   	struct in_addr addrptr;
   
  	// memset(&addrptr, '\0', sizeof(addrptr));
   // 	retval = inet_aton(argv[1], &addrptr);
	int PORT = atoi(argv[2]);
	printf("[-] Connecting to %s:%d\n", argv[1], PORT);

	int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "GET\r\n";
    char buffer[1024] = {0};

    // create a network socket 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Socket creation error \n");
        return -1;
    }


    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }

    send(sock , hello , strlen(hello) , 0 );
    printf("[-] Request sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;


}