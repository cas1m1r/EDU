#define _GNU_SOURCE 
// #include <sys/socket.h>
#include <stdint.h>
#include <stdio.h>
#include <dlfcn.h>

# define LOG_FILE "hooked.txt"
# define AF_INET 2

// struct sockaddr{
//     sa_family_t   sa_family;    //   address family
//     char          sa_data[];    //   socket address (variable-length data)
// };

int (*o_socket)(int,int,int);

int (*o_connect)(int , struct sockaddr *, int );

int (*o_send)(int, const void*, int, int);

int (*o_recv)(int, void*, int, unsigned int);

int socket(int domain, int type, int protocol){
    // find the next occurrence of the socket() function
    o_socket = dlsym(RTLD_NEXT, "socket");
    
    if(o_socket == NULL){
        printf("Could not find next socket() function occurrence");
        return -1;
    }
    printf("Call to socket() made.\n");
    return o_socket(domain,type,protocol);
}

int connect(int domain, struct sockaddr* s, int start){
	o_connect = dlsym(RTLD_NEXT, "connect");
	if(o_connect== NULL){
        printf("Could not find next socket() function occurrence");
        return -1;
    }
    printf("[-] Socket is calling connect()\n\n");
    return o_connect(domain,s, start);		
}

// // TODO: Hook Send
int send(int sockfd, const void *msg, int len, int flags){
	o_send = dlsym(RTLD_NEXT, "send");
	printf("[-] Socket is sending following data:\n %s\n\n", (char*)msg);
	//  Log information to a file
	return o_send(sockfd, msg, len, flags);
}


// // TODO: Hook Receive
int recv(int sockfd, void *buf, int len, unsigned int flags){
	o_recv = dlsym(RTLD_NEXT, "recv");
	printf("[-] Socket received the following data:\n %s\n\n", (char*)buf);
	// Log information to a file
	return o_recv(sockfd, buf, len, flags);
}



/* gcc -Wall -fPIC -shared -ldl -Wl,--no-as-needed sockhook.c -o shook.so */