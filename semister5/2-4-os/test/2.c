#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf(env);

void ringring(int sig) {
	longjmp(env, sig);
}

int main() {
	int val;

	signal(SIGALRM, ringring);
	alarm(10);

	if ((val = setjmp(env)) == 0) 
		for (;;)
			;
	else
		printf("val = %d\n", val);

	return 0;
}
