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
            tmp = strdup(strcat(juanito, "/"));
            tmp2 = strdup(strcat(tmp, parsed[0]));
            /*if (tmp2)
            {
                printf("%p\n", tmp2);
            }*/
            if (stat(tmp2, buf) == 0)
            {
                parsed[0] = tmp2;
                break;
            }
            if (tmp2)
                free(tmp2);
            h = h->next;
        }
    }
    if (buf)
        free(buf);
    if (tmp)
        free(tmp);
    if (juanito)
        free(juanito);
    /**/
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
        parsed[i] = malloc(sizeof(char) * strlen(dest));
        parsed[i] = strdup(dest);
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

paths_t *get_path(void)
{
    int i;
    char *tmp = NULL;
    paths_t *head;

    tmp = getenv("PATH");

    char **tmp2 = malloc(sizeof(char *) * (_strlen(tmp) + 1));
    parse_text_path(tmp, tmp2);
    head = NULL;

    i = 0;
    while (tmp2[i])
    {
        create_struct(&head, tmp2[i]);
        i++;
    }
    i = 0;

    while (tmp2[i])
    {
        free(tmp2[i]);
        i++;
    }
    if (tmp2)
        free(tmp2);
    /*print_list(head);*/
    return (head);
}
