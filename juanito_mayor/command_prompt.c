#include "shell.h"

/**
 * sigintHandler - Function to anulate the ^C
 * Description: There's no parameters inside this function
 *
 * Return: No returns in this function
 */

void sigintHandler(int nt)
{
	(void)nt;
	write(STDOUT_FILENO, "\n$(╯°□°）╯ ", _strlen("\n$(╯°□°）╯ "));
	fflush(stdout);
}

/**
 * command_promt - Function to open a prompt for our shell
 * @envp: Receive the arguments passed to shell
 *
 * Return: No returns in this function
 */

void command_promt(char **argv, char *envp[])
{
	char *parsed_args[1024];
	size_t nbytes = 32;
	char *buffer;
	paths_t *p_path_string;
	/*(paths_t *)malloc(sizeof(paths_t));*/

	p_path_string = get_path(envp);

	/**
	 * char cwd[1024];
	 * char *username;
	 * username = getlogin();
	 * getcwd(cwd, sizeof(cwd));
	 */

	signal(SIGINT, sigintHandler);
	while (1)
	{
		if (isatty(0))
			write(STDOUT_FILENO, "$(╯°□°）╯ ", _strlen("$(╯°□°）╯ "));
		buffer = malloc(sizeof(char) * nbytes);
		/*input_user = (char *)malloc(size_juanito);
		if (input_user == NULL)
		exit(0);*/
		/*
  parsed_args = NULL;*/
		/*parsed_args[1] = NULL;*/ /*   "esto soluciona el problema"*/
		if (getline(&buffer, &nbytes, stdin) != EOF)
		{
			if (buffer[0] != '\n' && buffer[0])
			{
				parse_text(buffer, parsed_args);
				call_func(buffer, argv, parsed_args, envp, p_path_string);
				free(buffer);
			}
			else
			{
				free(buffer);
				continue;
			}
		}
		else
		{
			free_list(p_path_string);
			free(buffer);
			break;
		}
	}

	/*if (p_path_string)
	{
		free_list(p_path_string);
		free(p_path_string);
		}*/
}
