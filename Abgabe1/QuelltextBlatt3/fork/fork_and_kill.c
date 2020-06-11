#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main(int argc, char* argv[]) {
	int i = fork();
	if(i == 0) {
		printf("Kindprozess: %d", getpid());
        while(1) {
            // do nothing
        }
	} else if(i > 0) {
		printf("Elternprozess: %d", i);
        sleep(20);
        kill(0, SIGKILL);
	} else {
		printf("error");
	}

	return 0;
}