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

} paths_t;

size_t print_list(paths_t *h);
char *_strdup(char *str);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
int _atoi(char *s);
char *_strtok(char *str, const char *delim);
void command_promt(char *envp[]);
void sigintHandler(int nt);
paths_t *get_path(char **env, char *comparation);
paths_t *create_struct(paths_t **head, char *str);
void parse_text_path(char *str, char **parsed);
void exec_args(char **parsed, char **env, paths_t *p_path_string);
void func_exit(char *buffer, char **parsed, paths_t *p_path_string);
void check_path(char **parsed, paths_t *h);
void parse_text(char *str, char **parsed);
void free_list(paths_t *head);
void free_parsed(char **parsed);

#endif /* JUANITO_SHELL */
