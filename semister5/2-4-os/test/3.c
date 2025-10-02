#include <stdio.h>
#include <stdlib.h>

int main() {
	int *p;

	p = (int *) main;
	printf("*p = %x\n", *p);

	*p = 0x20220726;
	printf("*p = %x\n", *p);

	return 0;
}
