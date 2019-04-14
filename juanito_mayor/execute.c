#include "shell.h"
/**
 * exec_args - Function to execute a process in child process
 * @parsed: string received
 * @env: Environment
 *
 * Return: No returns in this function
 */

void exec_args(char **argv, char **parsed, char **env, paths_t *p_path_string)
{
	int process, status = 0;
	char *parse = NULL;
	pid_t pid;

	parse = parsed[0];
	/**
	 * Forking a child
	 */
	parse = check_path(parse, p_path_string);

	/*print_list(p_path_string);*/
	pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		exit_num = 1;
		_exit(1);
	}
	else if (pid == 0)
	{
		process = execve(parse, parsed, env);
		if (process < 0)
		{
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, "1", 1);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, parsed[0], _strlen(parsed[0]));
			write(STDERR_FILENO, ": not found\n", 13);
			exit_num = 127;
			_exit(127);
		}
		_exit(0);
	}
	else
	{
		/**
		 * waiting for child to terminate
		 */
		exit_num = 0;
		free(parse);
		wait(&status);
		/*free(parse);*/
	}
}
