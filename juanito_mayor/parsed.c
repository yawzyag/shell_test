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
	char *dest;
	int i = 0;

	dest = strtok(str, delimiters);
	while (dest)
	{
		parsed[i] = dest;
		dest = strtok(NULL, delimiters);
		i++;
	}
/*cambio necesario!!!*/
	/*if (str)
		free(str);
	if (dest)
	free(dest);*/
}