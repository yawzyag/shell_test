#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <limits.h>

void sigintHandler()
{
    printf("\n$(╯°□°）╯");
    fflush(stdout);
}

int takeInput(char *str, char* buffer)
{
    if (strlen(buffer) != 0)
    {
        strcpy(str, buffer);
        return (0);
    }
    else
    {
        return 1;
    }
}

void parse_text(char *str, char **parsed)
{
    const char delimiters[] = " \n";
    char *dest;

    dest = strtok(str, delimiters);
    while (dest)
    {
        *parsed = dest;
        dest = strtok(NULL, delimiters);
    }
}

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
    }
}

void command_promt(char *envp[])
{
	char *input_user = malloc(sizeof(char) * 1024);
	char **parsed_args = malloc(sizeof(char) * 1024);
	ssize_t bytes_read;
	size_t nbytes = 0;
	char *buffer = malloc(sizeof(char) * 1024);
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
