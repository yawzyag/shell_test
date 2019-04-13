#include "shell.h"
/**
 * check_parse - Function to check the commands words
 * @parsed: string parsed where you can find a command word
 *
 * Return: No returns in this function
 */

void func_exit(char *buffer, char **parsed, paths_t *p_path_string)
{
	if (_strcmp(parsed[0], "exit") == 0)
	{
		if (parsed[1])
		{
			exit_num = _atoi(parsed[1]);
			if (exit_num)
			{
				free(parsed);
				if (buffer)
					free(buffer);
				if (p_path_string)
					free_list(p_path_string);
				exit(exit_num);
			}
		}
		if (buffer)
			free(buffer);
		if (p_path_string)
			free_list(p_path_string);
		free(parsed);
		exit(exit_num);
	}
}
