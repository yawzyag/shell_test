#include <stdio.h>
#include <stdlib.h>

/* To shorten example, not using argp */
int main (int argc, char *argv[], char *envp[])
{
	char *home, *host;

	home = getenv("HOME");
	host = getenv("USER");

	printf ("Your home directory is %s on %s.\n", home, host);

	return 0;
}
