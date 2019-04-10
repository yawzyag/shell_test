#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * _strtok(char *string, const char *delimiter)
{
	static char *temp;
	int chars = 0, flag = 0, i, len;

	len = strlen(delimiter);
	if (string != NULL)
	{
		temp = malloc(strlen(string));
		strcpy(temp, string);
	}
	else if (temp == NULL)
		return (NULL);
	else
	{
		string = temp;
	}
	while (*temp)
	{
		for (i = 0; i < len; i++)
		{
			if (*temp == delimiter[i])
			{
				if (chars == 0)
				{
					flag = 1;
					string++;
				}
				else
				{
					temp++;
					string[chars] = '\0';
					return string;
				}
			}
		}
		if (flag == 0)
			chars++;
		temp++;
		flag = 0;
	}
	temp = NULL;
	string[chars] = '\0';
	return (string);
}
