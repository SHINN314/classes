#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int i;

	for (i = 0; i < 2; i++) {
		int pid = fork();
		if (pid == -1) {
			perror("Error fork\n");
			exit(1);
		} else if (pid == 0) {
			// child process
			printf("child process\n");
		} else {
			// parent process
			wait(NULL);
			printf("parent process\n");
		}
	}

	return 0;
}
