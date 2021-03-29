#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include "socket.h"
#include "header.h"

#define PORT 8080
#define BUFFERLENGTHFORLISTENING 4

int main() {
	int sockid = createSocket(4, 0); // 4 - IPv4, 0 - TCP. These are just internally used.

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	bindSocket(sockid, addr);
	
	listenSocket(sockid, BUFFERLENGTHFORLISTENING);
	
//	int newSocketId = acceptSocketReq(sockid, addr);
	
	int addrSize = sizeof(addr);
        int newSocketId = accept(sockid, (struct sockaddr *) &addr, (socklen_t *)&addrSize);
	if(newSocketId == -1)
                printf("some problem connecting to client\n");
        else
                printf("connected to client and new socket id is %d\n", newSocketId);
	
	char *msg = "hello from server", buff[1024]={0};
	send(newSocketId, msg, strlen(msg), 0);

	recv(newSocketId, buff, 1024, 0);
	printf("received this message from client:- '%s'\n", buff);

	if(checkFileExistence(buff) == 1) {
		FILE *fp = fopen(buff, "r");
		printf("sending the contents of file %s\n", buff);
		bzero(buff, 1024);
		readFromFileAndSendData(fp, buff, newSocketId);
	}
	
	closeSocket(sockid);
	return 0;
}
