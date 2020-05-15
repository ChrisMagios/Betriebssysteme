#include "hello.h"

int writeToFile(char* name, const char* content) {

	int fd = 0;

	if ((fd = open(name, O_RDWR| O_CREAT | O_TRUNC, S_IRWXU)) == -1) {
		printf("Error while opening file...\n");
		exit(1);
	}
	

	if((write(fd, content, sizeof(content) + 4))== -1) {
		printf("Error while writing to file...\n");
		exit(1);
	}

	if(close(fd) == -1) {
		printf("Error while closing file descriptor...\n");
		exit(1);
	}

	return 0;
}

int writeToFileILA(char* name, const char* content) {

	int fd = 0;

	if ((fd = open(name, O_RDWR| O_CREAT | O_TRUNC, S_IRWXU)) == -1) {
		printf("Error while opening file...\n");
		exit(1);
	}
	
	int ret;
	int size = sizeof(content) + 4;
	asm volatile
	(
	"syscall"
	: "=a" (ret)
	: "a"(1), "D"(fd), "S"(content), "d"(size)
	: "cc", "rcx", "r11", "memory"
	);

	if(close(fd) == -1) {
		printf("Error while closing file descriptor...\n");
		exit(1);
	}

	return 0;
}
