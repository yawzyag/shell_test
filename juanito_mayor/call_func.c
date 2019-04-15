#include "shell.h"

/**
 *
 *
 *
 */

void call_func(char *buffer, char **argv, char **parsed, char **env, paths_t *p_path_string)
{
	if (!_strcmp(parsed[0], "exit"))
		func_exit(buffer, parsed, p_path_string);
	else
		{
			exec_args(buffer, argv, parsed, env, p_path_string);
		}
}
