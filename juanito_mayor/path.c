#include "shell.h"

char *check_path(char **parsed, paths_t *h)
{
    char *tmp = NULL;
    char *tmp2 = NULL;
    char *juanito = NULL;
    struct stat buf;
    char *slash = "/";
    char *var;

    var = parsed[0];

    tmp = str_concat(slash, var);
    /* buf = malloc(sizeof(struct stat));*/
    /*if (buf == NULL)
      return;*/
    if (!h)
	    return (NULL);
    while (h)
    {
        if (h->path)
        {
            juanito = _strdup(h->path);
            tmp2 = (str_concat(juanito, tmp));
            /*if (tmp2)
            {
                printf("%p\n", tmp2);
            }*/
            if (stat(tmp2, &buf) == 0)
            {
		    free(juanito);
		    free(tmp);
		    return (tmp2);
		printf("%s\n%s\n", tmp2, parsed[0]);
		/*free(juanito);*/
		break;
            }

/*            if (tmp2)
                free(tmp2);*/
            h = h->next;
        }
	free(tmp2);
	free(juanito);
	/*	if (tmp)
		free(tmp);
	if (juanito)
	*/	/*free(juanito);*/
    }
    free(tmp);
    return(parsed[0]);
    /* if (buf)
        free(buf);
    */
}

void parse_text_path(char *str, char **parsed)
{
    const char delimiters[] = "=:;";
    char *dest = NULL;
    int i;

    dest = strtok(str, delimiters);
    i = 0;
    while (dest)
    {
        parsed[i] = dest;
        dest = strtok(NULL, delimiters);
        i++;
    }
    parsed[i] = NULL;
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

paths_t *get_path(char **env)
{
	int i = 0, j = 0;
	char **juanito;
	int num, count;
	char *tmp;
	char **tmp2 = NULL;
	paths_t *head;
	char * comparation = "PATH";

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
    tmp2 = malloc(sizeof(char *) * 1024);
    parse_text_path(tmp, tmp2);
    head = NULL;

    i = 0;
    while (tmp2[i])
    {
        create_struct(&head, tmp2[i]);
        i++;
    }
    i = 0;

    if (tmp2)
        free(tmp2);
    /*print_list(head);*/
    return (head);
}
