#include "shell.h"

/**
 * free_list - Function get a line from stdin
 * @buf: Buffer allocated
 * @size: size of buffer
 * @stream: stdin
 *
 * Return: counter
 */

void free_list(paths_t *head)
{
	paths_t *tmp;

	while (head)
	{
		tmp = head->next;
		free(head->path);
		free(head);
		head = tmp;
	}
}

/**
 * free_parsed - Function to free arguments allocated in malloc
 * @parsed: The arguments to be free
 *
 * Return: No returns in this function
 */

void free_parsed(char **parsed)
{
	/*int i;

	while (parsed[i])
	{
		free(parsed[i]);
		i++;
		}*/
	if (parsed)
		free(parsed);
}
