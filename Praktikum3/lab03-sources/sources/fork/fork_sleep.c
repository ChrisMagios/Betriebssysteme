#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

int main(int argc, char* argv[]) {
	int pid = fork();
    pid_t pidc;
    if(pid == 0) {
        printf("Kindprozess: %d", getpid());
        sleep(30); 
        exit(0);
    } else if(pid > 0) {
        waitpid(0,0,0);
        printf("Elternprozess: %d", pid);
    }

	return 0;
}