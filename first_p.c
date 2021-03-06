#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

/**
 *
 *
 *
 *
 */

/* Signal Handler for SIGINT */
void sigintHandler(int sig_num)
{
	/* Reset handler to catch SIGINT next time.
	   Refer http://en.cppreference.com/w/c/program/signal */
	signal(SIGINT, sigintHandler);
	printf("\n$ ");
	fflush(stdout);
}

void print_env(char *envp[])
{
	while (*envp)
		printf("%s\n", *envp++);
}

void print_echo()
{
	char *av[3] = {"/bin/echo", "se muere", NULL};

	execve(av[0], av, NULL);
}

void print_ls()
{
	char *av[3] = {"/bin/ls", "-a", NULL};

	execve(av[0], av, NULL);
}

int get_token(char *str)
{

	// Returns first token
	char *token = strtok(str, "\n");
	char *dest;

	// Keep printing tokens while one of the 
	// delimiters present in str[]. 
	while (token != NULL)
	{
		dest = token;
		printf("%s\n", token);
		token = strtok(NULL, "\n");
	}
	printf("JUANITO DEST FUERA DE WILLI: %s\n", dest);
	if (dest)
	{
		print_ls();
	}
	return (0);
}

void loop(char *av[], char *envp[])
{
	ssize_t bytes_read;
	size_t nbytes = 0;
	char *buffer = NULL;
	char *my_string; //*av[3] = {"/bin/echo", "-se suelta-", NULL};
	pid_t childp;
	int status;
	char *clave[1];

	signal(SIGINT, sigintHandler);
	while (1)
	{
		printf("$ ");

		/* These 2 lines are the heart of the program. */
		//buffer = (char *) malloc(sizeof(nbytes));
		bytes_read = getline(&buffer, &nbytes, stdin);
		clave[0] = strtok(buffer, "\n");
		if (bytes_read == -1)
		{
			printf("You can't kill JUANITO!!!\n");

		}
		else
		{
			childp = fork();
			if (childp == -1)
			{
				perror("Error: Juanito no funciona");
				exit(-1);
			}
			if (childp != 0)
			{
				printf("$ Yo soy tu Padre\n");
				wait(&status);
			}
			else
			{
				//if (clave[0] == "NTP")
				//	exit(98);
				printf("$ NOOOOOOOOOOOOOOOOOOOOO...\n");
				sleep(2);
				get_token(buffer);
				//if (buffer == "ls")
				//	print_ls();
				//print_ls();
				//	print_env(envp);
				//print_echo();
			}
		}
	}

}

int main(int ac __attribute__((unused)), char **av, char *envp[])
{
	loop(av, envp);

	return (0);
}
