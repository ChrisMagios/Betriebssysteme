#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	int i = fork();
	if(i == 0) {
		printf("Kindprozess: %d", i);
	} else if(i > 0) {
		printf("Elternprozess: %d", i);
	} else {
		printf("error");
	}

	return 0;
}
