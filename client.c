#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

#include "socket.h"

#define PORT 8080
#define BUFFERLENGTHFORLISTENING 4

int main() {
        int sockid = createSocket(4, 0); // 4 - IPv4, 0 - TCP. These are just internally used.

        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");        

	connectToSocket(sockid, addr);
	
	char *msg = "hello from client", buff[1024]={0};
	send(sockid, msg, strlen(msg), 0);	

	recv(sockid, buff, 1024, 0);
	printf("received this message from server:- '%s'\n", buff);

        closeSocket(sockid);
        return 0;
}