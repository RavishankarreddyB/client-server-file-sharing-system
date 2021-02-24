server client: server.c client.c socket.h
	gcc server.c -o server -Wall -Wextra -std=c17
	gcc client.c -o client -Wall -Wextra -std=c17 
