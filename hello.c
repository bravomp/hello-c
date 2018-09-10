#include <stdio.h>
#include <stdlib.h>

int unused_func ()
{
	int i;
	int overrun[10];
	char *leak;
	char *unused = "unused string";

	if (i) {
		printf ("uninitialized variable\n");
	}

	for (i=0; i<=10; i++) {
		overrun[i] = i;
	}

	leak = malloc(256);

	return(0);
	printf ("structurally dead code\n");
}

int main (int argc, char **argv)
{
	int unused;
	char *ptr = NULL;

	if (argc < 0) {
		printf ("abnormal termination\n");
		abort ();
	}

	if (ptr != ptr) {
		printf ("same on both sides\n");
	}

	if (ptr != NULL) {
		printf ("logically dead code\n");
	}

	printf ("hello world\n");
	return(0);
}
