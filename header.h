#include <unistd.h>

int checkFileExistence(char* fileName) {
	int returnValue = access(fileName, F_OK);
	if(returnValue == 0) {
		printf("file exits\n");
		return 1;
	}
	else {
		printf("file doesn't exist\n");
		return -1;
	}
}
