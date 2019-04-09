#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


ssize_t get_line(char *buffer, size_t size, FILE *stream)
{
	ssize_t count = 0;
	char my_char;
    
	while ((my_char = (char) getc(stream)) != '\n'&& count < size -1)
	{
		buffer [count++] = my_char;
	}
    
	buffer [count] = '\0';
	return (count);
}

void parse_text(char *str, char **parsed)
{
	const char delimiters[] = "=:";
	char *dest;
	int i = 0;

	dest = strtok(str, delimiters);
	while (dest)
	{
		parsed[i] = dest;
		dest = strtok(NULL, delimiters);
		i++;
	}
	/**
	 * if (dest)
	 * free(dest);
	 */
}

char *get_path(char **env, char *comparation)
{
	int i = 0, j = 0;
	char **juanito;
	int num, count;
	char *tmp;
	char **tmp2 = malloc(sizeof(char) * 1024);
	char *dest;
    
	juanito = env;
    
	while(juanito[i] != NULL)
	{
		j = 0;
		count = 0;
		while(juanito[i][j])
		{
			if(juanito[i][j] == comparation[j] && j < 4)
			{
				count++;
				if(count == 4 && j == 3)
					num = i;
			}
			else
				count = 0;
			j++;
		}
        
		i++;
	}
	tmp = juanito[num];
	printf("%s\n", tmp);
    
	parse_text(tmp, tmp2);
    
	printf("%d\n", num);
	while (*tmp2)
	{
		printf("%s\n", *tmp2++);
	}
	exit(0);
}

int main (int argc, char *argv[], char **env)
{
	int counter = 1;
	ssize_t bytes; 
	size_t line = 0;
	char *buffer;
	char *path_string;
	char *path;
    
	path = "PATH";
	path_string = get_path(env, path);
   
	while (1)
        {
		buffer = malloc(sizeof(char) * 1024);
		bytes = get_line(buffer, line, stdin);
		printf ("%s\n", buffer);
        }
}
