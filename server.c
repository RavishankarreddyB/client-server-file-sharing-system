#include <stdio.h>
#include <netinet/in.h>
#include <string.h>

#include "socket.h"

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
	
	int newSocketId = acceptSocketReq(sockid, addr);

	char *msg = "hello from server", buff[1024]={0};
	send(newSocketId, msg, strlen(msg), 0);

	recv(newSocketId, buff, 1024, 0);
	printf("received this message from client:- '%s'\n", buff);
	
	closeSocket(sockid);
	return 0;
}
