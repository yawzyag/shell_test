#include "shell.h"

/**
 * parse_text - Function to parse a string by their tokens
 * @str: String received to be parsed
 * @parsed: String parsed by strtok function
 *
 * Return: No returns, just dest to allocate the string
 */

void parse_text(char *str, char **parsed)
{
	const char delimiters[] = " \n\"";
	char *dest = NULL;
	char **tmp = NULL;
	int i = 0;

	tmp = parsed;

	dest = strtok(str, delimiters);
	while (dest)
	{
		tmp[i] = dest;
		dest = strtok(NULL, delimiters);
		i++;
	}
	tmp[i] = NULL;
	parsed = tmp;
	free(dest);
	/*cambio necesario!!!*/
	/*if (str)
		free(str);
	if (dest)
	free(dest);*/
}
