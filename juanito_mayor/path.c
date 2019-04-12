#include "shell.h"

void check_path(char **parsed, paths_t *h)
{
	char *tmp = NULL;
	char *tmp2 = NULL;
	char *juanito = NULL;
	struct stat *buf;

	buf = malloc(sizeof(struct stat));
	if (buf == NULL)
		return;
	if (!h)
		return;
	while (h)
	{
		if (h->path)
		{

			juanito = _strdup(h->path);
			tmp = strcat(juanito, "/");
			tmp2 = strcat(tmp, parsed[0]);
			printf("%s\n", parsed[0]);
			/*if(tmp2)
			  {
			  printf("%s\n",tmp2);
			  }*/
			if (stat(tmp2, buf) == 0)
			{
				parsed[0] = tmp2;
				/*if(tmp2)
				  free(tmp2);*/
				printf("%s\n", parsed[0]);
				break;
			}
			/*if(tmp2)
			  free(tmp2);*/
			h = h->next;
		}
	}
	if(buf)
		free(buf);

	/*if (tmp2)
	  free(tmp2);*/
}


void parse_text_path(char *str, char **parsed)
{
	const char delimiters[] = "=:";
	char *dest = NULL;
	int i = 0;

	dest = strtok(str, delimiters);
	while (dest)
	{
		parsed[i] = dest;
		dest = strtok(NULL, delimiters);
		i++;
	}
	if (dest)
		free(dest);
}


paths_t *create_struct(paths_t **head, char *str)
{
	paths_t *new_node = (paths_t *)malloc(sizeof(paths_t));

	if (!new_node)
		return (NULL);
	new_node->path = _strdup(str);
	if (!new_node->path)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = *head;
	*head = new_node;

	return (new_node);
}

paths_t *get_path(char **env, char *comparation)
{
	int i = 0, j = 0;
	char **juanito;
	int num, count;
	char *tmp;
	char **tmp2;
	paths_t *head;

	tmp2 = (char **)malloc(sizeof(char *) * 1024);
	juanito = env;
	while (juanito[i] != NULL)
	{
		j = 0;
		count = 0;
		while (juanito[i][j])
		{
			if (juanito[i][j] == comparation[j] && j < 4)
			{
				count++;
				if (count == 4 && j == 3)
					num = i;
			}
			else
				count = 0;
			j++;
		}
		i++;
	}
	tmp = juanito[num];
	parse_text_path(tmp, tmp2);
	head = NULL;

	i = 0;
	while (tmp2[i])
	{
		create_struct(&head, tmp2[i]);
		i++;
	}
	free(tmp2);
	/*print_list(head);*/
	return (head);
}
