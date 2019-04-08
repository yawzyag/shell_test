#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void sighandler(int sig_num)
{
	printf("\nThe_prompt$: ");
	fflush(stdout);
}

int main(int argc, char *argv[], char *envp[])
{
	pid_t child0;
	size_t characters, buffsize = 32;
	char *buffer, tokens;
	int status;

	signal(SIGINT, sighandler);
	while (1)
	{
		printf("The_prompt$: ");
		buffer = malloc(buffsize * sizeof(char));
		characters = getline(&buffer, &buffsize, stdin);
		if (buffer == NULL)
		{
			perror("Unable to allocate buffer");
			exit(98);
		}
		child0 = fork();
		if (child0 == -1)
		{
			perror("Error:");
			return (1);
		}
		if (child0 != 0)
		{
			wait(&status);
		}
		else
		{
			printf("\nIn execution...\n");
			sleep(1);
			printf("%zu characters were read.\n", characters);
			printf("You typed: '%s'\n", buffer);
			printf("$ ");
/*			execve(argv[0], argv, NULL);
*/		}
	if (strcmp(buffer, "exit") == 0)
		break;
	}
return (0);
}
