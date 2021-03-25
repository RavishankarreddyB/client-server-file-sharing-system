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
	
	char buff[1024]={0}, fileName[1024]={0};
	
	printf("enter the filename:\n");
	fgets(fileName, 1024, stdin);
	
	// fgets adds \n at the end of input string. So the below line removes it.	
	fileName[strcspn(fileName, "\n")]=0;

	printf("file name reqeusting is %s\n", fileName);
	send(sockid, fileName, strlen(fileName), 0);	

	recv(sockid, buff, 1024, 0);
	printf("received this message from server:- '%s'\n", buff);

	// to get the file name in the format "copy_fileName"	
	char copy_fn[1024] = "copy_";
	strcat(copy_fn, fileName);

	FILE *fp = fopen(copy_fn, "w");
	receiveDataAndWriteToFile(fp, buff, 1024, sockid);

        closeSocket(sockid);
        return 0;
}
