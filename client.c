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
	
	char buff[1024]={0};
	
	printf("enter the filename:\n");
	fgets(buff, 1024, stdin);
	printf("file name reqeusting is %s\n", buff);
	send(sockid, buff, strlen(buff)-1, 0); // \n is stored at the buff by fgets. so effective length is len-1	

	recv(sockid, buff, 1024, 0);
	printf("received this message from server:- '%s'\n", buff);

	FILE *fp = fopen("dummy_file", "w");
	receiveDataAndWriteToFile(fp, buff, 1024, sockid);

        closeSocket(sockid);
        return 0;
}
