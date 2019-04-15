#include "shell.h"
/**
 * check_parse - Function to check the commands words
 * @parsed: string parsed where you can find a command word
 *
 * Return: No returns in this function
 */

void func_exit(char *buffer, char **parsed, paths_t *p_path_string)
{
	int exit_num = 0;

	if (_strcmp(parsed[0], "exit") == 0)
	{
		if (parsed[1])
		{
			exit_num = _atoi(parsed[1]);
			if (exit_num)
			{
				free(parsed);
				free(buffer);
				free_list(p_path_string);
				_exit(exit_num);
			}
		}
		free(buffer);
		free_list(p_path_string);
		_exit(0);
	}
}
