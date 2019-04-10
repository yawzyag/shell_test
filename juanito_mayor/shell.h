#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <limits.h>

/**
 * path_s - Function to anulate the ^C
 * Description: There's no parameters inside this function
 *
 * Return: No returns in this function
 */

typedef struct path_s
{
	char *path;
	struct path_s *next;

}paths_t;

size_t print_list(const paths_t *h);
char *_strdup(char *str);
int _strlen(char *s);

#endif /* JUANITO_SHELL */
