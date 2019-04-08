#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <limits.h>

void sigintHandler(int sig_num)
{
    /* Reset handler to catch SIGINT next time.
	   Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sigintHandler);
    printf("\n(╯°□°）╯");
    fflush(stdout);
}

int takeInput(char *str)
{
    ssize_t bytes_read;
    size_t nbytes = 0;
    char *buffer = NULL;

    bytes_read = getline(&buffer, &nbytes, stdin);
    if (bytes_read == -1)
    {
        printf("You must not kill JUANITO!!!\n");
        /*exit(1);*/
    }
    if (strlen(buffer) != 0)
    {
        strcpy(str, buffer);
        return 0;
    }
    else
    {
        return 1;
    }
}

void parse_text(char *str, char **parsed)
{
    printf("%s\n", str);
    int i;
    const char delimiters[] = " \n";
    char *dest;

    dest = strtok(str, delimiters);
    while (dest)
    {
        *parsed = dest;
        printf("%s\n", dest);
        dest = strtok(NULL, delimiters);
    }
}

char *check_parse(char **parsed)
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
        return;
    }
}

void command_promt(char **av, char *envp[])
{
    char input_user[1024];
    int i = 0;
    char *parsed_args[1024];

    signal(SIGINT, sigintHandler);

    while (1)
    {
        printf("(╯°□°）╯ ");

        if (takeInput(input_user))
            continue;

        parse_text(input_user, parsed_args);

        exec_args(parsed_args, envp);
    }
}

int main(int ac __attribute__((unused)), char **av, char *envp[])
{
    command_promt(av, envp);

    return (0);
}
