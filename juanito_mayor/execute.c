#include "shell.h"
/**
 * exec_args - Function to execute a process in child process
 * @parsed: string received
 * @env: Environment
 *
 * Return: No returns in this function
 */

void exec_args(char *buffer, char **argv, char **parsed, char **env, paths_t *p_path_string)
{

	int status;
	pid_t pid, tpid;
	char *text_parsed;

	(void)argv;
	/**
	 * Forking a child
	 */
	pid = fork();

	if(pid == 0)
	{
		text_parsed = check_path(parsed, p_path_string);
		if(execve(text_parsed, parsed, env) == -1)
		{
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, "1", 1);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, text_parsed, _strlen(text_parsed));
			write(STDERR_FILENO, ": not found\n", 13);
			free(buffer);
			free_list(p_path_string);
		 }
		exit(0);
	}
	else
	{
		do {
			tpid = wait(&status);
		}
		while(tpid != pid);
	}
	free(buffer);
	/*pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		free_list(p_path_string);
		free(buffer);
		_exit(1);
	}
	else if (pid == 0)
	{
		process = execve(text_parsed, parsed, env);
		if (process < 0)
		{
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, "1", 1);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, text_parsed, _strlen(text_parsed));
			write(STDERR_FILENO, ": not found\n", 13);
			free_list(p_path_string);
			free(buffer);
			_exit(127);
		}
	}
	else
	{
		*
		 * waiting for child to terminate
		 
		wait(&status);
		free(text_parsed);
		printf("%s\n", buffer);
		printf("dshjksd");
	}*/
}
