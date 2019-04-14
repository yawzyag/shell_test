#include "shell.h"

int exit_num = 0;

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
	/*int size_juanito = 1024;*/
	/*char *input_user;*/
	char **parsed_args;
	ssize_t bytes_read;
	size_t nbytes = 0;
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
		buffer = NULL;
		/*input_user = (char *)malloc(size_juanito);
		if (input_user == NULL)
		exit(0);*/
		/*
  parsed_args = NULL;*/
		parsed_args = (char **)malloc(sizeof(char *) * 1024);
		parsed_args[1] = NULL; /*   "esto soluciona el problema"*/
		bytes_read = getline(&buffer, &nbytes, stdin);
		if (bytes_read == -1)
		{
			if (buffer)
				free(buffer);
			if (p_path_string)
				free_list(p_path_string);
			if (parsed_args)
				free(parsed_args);
			/*printf("You can't kill JUANITO!!!\n");*/
			/**
			 * this line need to be commented
			 */
			/*write(STDOUT_FILENO, "\n", _strlen("\n"));*/
			exit(exit_num);
		}
		if (buffer[0] != '\n' && buffer[0])
		{
			parse_text(buffer, parsed_args);
			func_exit(buffer, parsed_args, p_path_string);
			exec_args(argv, parsed_args, envp, p_path_string);
		}
		if (parsed_args)
		  free_parsed(parsed_args);
		free(buffer);
	}
	free(buffer);
	if (p_path_string)
	{
		free_list(p_path_string);
		free(p_path_string);
	}
}
