#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <limits.h>

/**
 * sigintHandler - Function to anulate the ^C
 * Description: There's no parameters inside this function
 *
 * Return: No returns in this function
 */

void sigintHandler()
{
	printf("\n$(╯°□°）╯");
	fflush(stdout);
}


/**
 * _getline - Function get a line from stdin
 * @buf: Buffer allocated
 * @size: size of buffer
 * @stream: stdin
 *
 * Return: counter
 */

ssize_t _getline(char *buf, size_t size, FILE *stream)
{
	ssize_t count = 0;
	char c;
	while ((c = (char)getc(stream)) != '\n' && count < size - 1)
		buf[count++] = c;
	buf[count] = '\0';
	return (count);
}


/**
 * free_parsed - Function to free arguments allocated in malloc
 * @parsed: The arguments to be free
 *
 * Return: No returns in this function
 */

void free_parsed(char **parsed)
{
	int i;

	if (parsed != NULL)
	{
		for (i = 0; parsed[i];)
		{
			i++;
		}
		i - 1;
		for (; parsed[i] == NULL; i--)
		{
			free(parsed[i]);
		}
		free(parsed[0]);
		free(parsed);
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
	/**
	 * if (dest)
	 * free(dest);
	 */
}

/**
 * check_parse - Function to check the commands words
 * @parsed: string parsed where you can find a command word
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

/**
 * exec_args - Function to execute a process in child process
 * @parsed: string received
 * @env: Environment
 *
 * Return: No returns in this function
 */

void exec_args(char **parsed, char **env)
{
	int process;
	/**
	 * Forking a child
	 */
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
		/**
		 * waiting for child to terminate
		 */
		wait(NULL);
		if (parsed)
			free_parsed(parsed);
	}
}

/**
 * command_promt - Function to open a prompt for our shell
 * @envp: Receive the arguments passed to shell
 *
 * Return: No returns in this function
 */

void command_promt(char *envp[])
{
	int size_juanito = 1024;
	char *input_user;
	char **parsed_args;
	ssize_t bytes_read;
	size_t nbytes = 0;
	char *buffer;
	int atty = isatty(0);
	/**
	 * char cwd[1024];
	 * char *username;
	 * username = getlogin();
	 * getcwd(cwd, sizeof(cwd));
	 */

	signal(SIGINT, sigintHandler);
	while (1)
	{
		if (atty)
			printf("$(╯°□°）╯ ");
		buffer = malloc(sizeof(char) * size_juanito);
		bytes_read = _getline(buffer, nbytes, stdin);
		input_user = malloc(sizeof(char) * size_juanito);
		parsed_args = malloc(sizeof(char) * size_juanito);
		if (bytes_read == -1)
		{
			printf("You can't kill JUANITO!!!\n");
/**
 * this line need to be commented
*/
			exit(98);
		}
		if (buffer[0] != '\n')
		{
			takeInput(input_user, buffer);
			if (buffer)
			  free(buffer);
			parse_text(input_user, parsed_args);
			exec_args(parsed_args, envp);
		}
	}
}

/**
 * main - Entry Point
 * @ac: counter of arguments
 * @av: arguments received in shell
 * @envp: environment
 *
 * Return: Always 0 (success)
 */

int main(int ac, char **av, char *envp[])
{
	(void)ac;
	(void)av;
	command_promt(envp);

	return (0);
}
