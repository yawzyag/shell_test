#include "shell.h"
/**
 * exec_args - Function to execute a process in child process
 * @parsed: string received
 * @env: Environment
 *
 * Return: No returns in this function
 */

void exec_args(char **parsed, char **env, paths_t *p_path_string)
{
	int process;
	pid_t pid;
	/**
	 * Forking a child
	 */
	func_exit(parsed, p_path_string);
	check_path(parsed, p_path_string);
	/*print_list(p_path_string);*/
	pid = fork();

	if (pid == -1)
	{
		printf("\nFailed fork in juanito :c..");
		return;
	}
	else if (pid == 0)
	{
		process = execve(parsed[0], parsed, env);
		printf("process %i : ", process);
		if (process < 0)
		{
			printf("Error juanito no process\n");
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