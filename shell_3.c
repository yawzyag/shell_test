#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <limits.h>

/**
 * siginthandler - Function to anulate the ^C
 * Description: There's no parameters inside this function
 *
 * Return: No returns in this function
 */

void sigintHandler()
{
	printf("\n$(╯°□°）╯");
	fflush(stdout);
}

void free_grid(char **grid)
{
	int i;

	if (grid != NULL)
	{
		for (i = 0; grid[i]; i++)
			free(*(grid + i));

		free(grid);
	}
}

/**
 * takeInput - Function to take the input and copy it.
 * @str: Copy of the string inside the function
 * @buffer: String inside the buffer to be copied
 *
 * Return: always 1 if success, in other case 0
 */

int takeInput(char *str, char *buffer)
{
	if (strlen(buffer) != 0)
	{
		strcpy(str, buffer);
		return (0);
	}
	else
	{
		return (1);
	}
}

/**
 * parse_text - Function to parse a string by their tokens
 * @str: String received to be parsed
 * @parsed: String parsed by strtok function
 *
 * Return: No returns, just dest to allocate the string
 */

void parse_text(char *str, char **parsed)
{
	const char delimiters[] = " \n\"";
	char *dest;
	int i = 0;

	dest = strtok(str, delimiters);
	while (dest)
	{
		parsed[i] = dest;
		dest = strtok(NULL, delimiters);
		i++;
	}
}

/**
 * check_parse - Function to anulate the ^C
 * Description: There's no parameters inside this function
 *
 * Return: No returns in this function
 */

void check_parse(char **parsed)
{
	char *a = malloc(256);

	if (strcmp(parsed[0], "ls") == 0)
	{
		strcpy(a, "/bin/ls");
		parsed[0] = a;
	}
	else if (strcmp(parsed[0], "pwd") == 0)
	{
		strcpy(a, "/bin/pwd");
		parsed[0] = a;
	}
	else if (strcmp(parsed[0], "env") == 0)
	{
		strcpy(a, "/usr/bin/env");
		parsed[0] = a;
	}
	else if (strcmp(parsed[0], "echo") == 0)
	{
		strcpy(a, "/bin/echo");
		parsed[0] = a;
	}
	else if (strcmp(parsed[0], "nano") == 0)
	{
		strcpy(a, "/bin/nano");
		parsed[0] = a;
	}
	else if (strcmp(parsed[0], "exit") == 0)
	{
		if (parsed[1])
		{
			if (atoi(parsed[1]))
				exit(atoi(parsed[1]));
		}
		exit(0);
	}
}

void exec_args(char **parsed, char **env)
{
	int process;
	/* Forking a child */
	pid_t pid = fork();
	check_parse(parsed);
	if (pid == -1)
	{
		printf("\nFailed fork in juanito :c..");
		return;
	}
	else if (pid == 0)
	{
		process = execve(parsed[0], parsed, env);
		printf("process %i\n", process);
		if (process < 0)
		{
			printf("\nError juanito no process");
		}
		exit(0);
	}
	else
	{
		/* waiting for child to terminate */
		wait(NULL);
		if (parsed)
			free_grid(parsed);
	}
}

void command_promt(char *envp[])
{
	int size_juanito = 1024;
	char *input_user = malloc(sizeof(char) * size_juanito);
	char **parsed_args = malloc(sizeof(char) * size_juanito);
	ssize_t bytes_read;
	size_t nbytes = 0;
	char *buffer = malloc(sizeof(char) * size_juanito);
	int atty = isatty(0);
	/*char cwd[1024];
	  char *username;

	  username = getlogin();

	  getcwd(cwd, sizeof(cwd));*/

	signal(SIGINT, sigintHandler);
	while (1)
	{
		if(atty)
			printf("$(╯°□°）╯ ");

		bytes_read = getline(&buffer, &nbytes, stdin);
		if (bytes_read == -1)
		{
			printf("You can't kill JUANITO!!!\n"); /*this line need to be commented*/
			exit(98);
		}
		if (buffer[0] != '\n')
		{
			if (takeInput(input_user, buffer))
				break;
			parse_text(input_user, parsed_args);
			exec_args(parsed_args, envp);
		}
	}
}

int main(int ac __attribute__((unused)), char **av __attribute__((unused)), char *envp[])
{
	command_promt(envp);

	return (0);
}
