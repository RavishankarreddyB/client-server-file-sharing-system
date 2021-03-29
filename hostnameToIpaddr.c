#include <stdio.h>
#include <netdb.h> // for hostent structure.
#include <string.h>
#include <arpa/inet.h> // for inet_ntoa function.

/*

// Description of data base entry for a single host.

struct hostent
{
	char *h_name;			// Official name of host.
	char **h_aliases;		// Alias list.
	int h_addrtype;		// Host address type.
	int h_length;			// Length of address.
	char **h_addr_list;		// List of addresses from name server. This will have address in long format.
};

*/

/*

the function gethostbyname() takes domain/host name as parameter and will return a structure of type of hostent which has the IP information (h_addr_list).

inet_ntoa() converts ip address in long format to dotted format.
inet_addr() converts ip address in dotted format to long format.

*/

int main() {
	// char *hostName = "www.google.com";
	char ip[256], hostName[2048];

	fgets(hostName, 2048, stdin);
	hostName[strcspn(hostName, "\n")] = 0;

	struct hostent *hostDetails;
	struct in_addr **addr_list;
	if( (hostDetails = gethostbyname(hostName)) == NULL ) {
		printf("couldn't get ip address for the given host name\n");
		return 0;
	}
	addr_list = (struct in_addr **) hostDetails->h_addr_list;
	
	for(int i=0; addr_list[i] != NULL; i++) {
		strcpy(ip, inet_ntoa(*addr_list[i]));
		printf("%s\n", ip);
	}
	printf("%s is converted to %s\n", hostName, ip);
}
