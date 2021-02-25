#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int createSocket(int ip_version, int tcp_or_udp) {
	int sockid = 0;
	if(ip_version == 4) {
		if(tcp_or_udp == 0)
			sockid = socket(AF_INET, SOCK_STREAM, 0);
		else if(tcp_or_udp == 1)
			sockid = socket(AF_INET, SOCK_DGRAM, 0);
	}
	else if(ip_version == 6) {
		if(tcp_or_udp == 0)
			sockid = socket(AF_INET6, SOCK_STREAM, 0);
		else if(tcp_or_udp == 1)
			sockid = socket(AF_INET6, SOCK_DGRAM, 0);
	}
	if(sockid == -1)
		printf("socket is not created\n");
	else
		printf("socket %d is created successfully\n", sockid);
	return sockid;
}

void bindSocket(int sockid, struct sockaddr_in addr) {
	int returnValue = bind(sockid, (struct sockaddr *) &addr, sizeof(addr));
	if(returnValue == -1)
		printf("some problem binding IP and PORT to socket\n");
	else
		printf("IP and PORT are successfully binded to socket\n");
}

void listenSocket(int sockid, int buffer_length) {
	int returnValue = listen(sockid, buffer_length);
	if(returnValue == -1)
		printf("could not listen\n");
	else
		printf("listening...\n");
}

int acceptSocketReq(int sockid, struct sockaddr_in addr) {
	int addrSize = sizeof(addr);
	int newSocketId = accept(sockid, (struct sockaddr *) &addr, (socklen_t *)&addrSize);
	if(newSocketId == -1)
		printf("some problem connecting to client\n");
	else
		printf("connected to client and new socket id is %d\n", newSocketId);
	return newSocketId;
}

void connectToSocket(int sockid, struct sockaddr_in addr) {
	int returnValue = connect(sockid, (struct sockaddr *) &addr, sizeof(addr));
	if(returnValue == -1)
		printf("some problem in connecting to server\n");
	else
		printf("connected to server\n");
}

void closeSocket(int sockid) {
	printf("closing the socket %d\n", sockid);
	close(sockid);
}

void readFromFileAndSendData(FILE *fp, char* buff, int size, int sockid) {
        while(fgets(buff, size, fp) != NULL) {
		send(sockid, buff, size, 0);
		bzero(buff, size);
	}
}

void receiveDataAndWriteToFile(FILE *fp, char* buff, int size, int sockid) {
	while(1) {
		bzero(buff, size);
		int n=recv(sockid, buff, size, 0);
		if(n<=0)
			break;
		fprintf(fp, "%s", buff);
	}
}
