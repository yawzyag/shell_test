#include "shell.h"
/**
 * check_parse - Function to check the commands words
 * @parsed: string parsed where you can find a command word
 *
 * Return: No returns in this function
 */

void func_exit(char *buffer, char **parsed, paths_t *p_path_string)
{
	int num;

	num = 0;
	if (_strcmp(parsed[0], "exit") == 0)
	{
		if (parsed[1])
		{
			num = _atoi(parsed[1]);
			if (num)
			{
				free(parsed);
				if (buffer)
					free(buffer);
				if (p_path_string)
					free_list(p_path_string);
				exit(num);
			}
		}
		if (buffer)
			free(buffer);
		if (p_path_string)
			free_list(p_path_string);
		free(parsed);
		exit(0);
	}
}
