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
	printf("\n$(╯°□°）╯");
	fflush(stdout);
}

/**
 * command_promt - Function to open a prompt for our shell
 * @envp: Receive the arguments passed to shell
 *
 * Return: No returns in this function
 */

void command_promt(char *envp[])
{
	/*int size_juanito = 1024;*/
	/*char *input_user;*/
	char **parsed_args;
	ssize_t bytes_read;
	size_t nbytes = 0;
	char *buffer;
	paths_t *p_path_string;
	char *path;

	p_path_string = NULL;
		/*(paths_t *)malloc(sizeof(paths_t));*/
	path = "PATH";
	p_path_string = get_path(envp, path);

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
			printf("$(╯°□°）╯ ");
		buffer = NULL;
		/*input_user = (char *)malloc(size_juanito);
		if (input_user == NULL)
		exit(0);*/
		parsed_args = (char **)malloc(sizeof(char) * 1024);
		parsed_args[1] = NULL;/*   "Aparentemente esto "soluciona el problema""*/
		/*printf("parsed[1]: %s\n", parsed_args[1]);
		if (parsed_args == NULL)
		exit(0);*/
		bytes_read = getline(&buffer, &nbytes, stdin);
		if (bytes_read == -1)
		{
			free(buffer);
			free_list(p_path_string);
			/*free(p_path_string);*/
			free(parsed_args);
			/*free(input_user);*/
			printf("You can't kill JUANITO!!!\n");
			/**
			 * this line need to be commented
			 */
			exit(0);
		}
		if (buffer[0] != '\n')
		{
			/*input_user = buffer;*/
			/*_strcpy(input_user, buffer);    "ESTO NUNCA
			  if (buffer)                  FUE NECESARIO :)"
			  free(buffer);*/
			parse_text(buffer, parsed_args);
			exec_args(parsed_args, envp, p_path_string);
		}
		free(buffer);
		/*if (parsed_args)
			free_parsed(parsed_args);*/
		/*if (input_user)*/ /*funciona ... a veces*/
		/*free(input_user);*/
	}
	free(buffer);
	if (p_path_string)
	{
		free_list(p_path_string);
		free(p_path_string);
	}
}
