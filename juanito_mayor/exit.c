#include "shell.h"
/**
 * check_parse - Function to check the commands words
 * @parsed: string parsed where you can find a command word
 *
 * Return: No returns in this function
 */

void func_exit(char **parsed, paths_t *p_path_string)
{
	if (_strcmp(parsed[0], "exit") == 0)
	{
		if (p_path_string)
		{
			free_list(p_path_string);
			free(p_path_string);
		}
		if (parsed[1])
		{
			if (_atoi(parsed[1]))
				exit(_atoi(parsed[1]));
		}
		exit(0);
	}
}