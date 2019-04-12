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


/**
 * takeInput - Function to take the input and copy it.
 * @str: Copy of the string inside the function
 * @buffer: String inside the buffer to be copied
 *
 * Return: always 1 if success, in other case 0
 */
/* "NO HACE ABSOLUTAMENTE NADA DIFERENTE A COPIAR UN STRING :)"
int takeInput(char *str, char *buffer)
{
	if (_strlen(buffer) != 0)
	{
		_strcpy(str, buffer);
		return (0);
	}
	else
	{
		return (1);
	}
}*/

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

void check_path(char **parsed, paths_t *h)
{
	char *tmp = NULL;
	char *tmp2 = NULL;
	char *juanito = NULL;
	struct stat *buf;

	if (_strlen(parsed[0]) < 9)
	{
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
				tmp = _strdup(strcat(juanito, "/"));
				tmp2 = _strdup(strcat(tmp, parsed[0]));
				if (stat(tmp2, buf) == 0)
				{
					parsed[0] = tmp2;
					break;
				}
				h = h->next;
			}
		}
	}
	free(juanito);
	free(tmp);
	/*if (tmp2)  "Se necesita, pero hay que esperar y ver"
	  free(tmp2);*/
}

/**
 * check_parse - Function to check the commands words
 * @parsed: string parsed where you can find a command word
 *
 * Return: No returns in this function
 */

void func_exit(char **parsed, paths_t *p_path_string)
{
	if (_strcmp(parsed[0], "exit") == 0)
	{
		if (p_path_string)
		{
			free_list(p_path_string);
			free(p_path_string);
		}
		if (parsed[1])
		{
			if (_atoi(parsed[1]))
				exit(_atoi(parsed[1]));
		}
		exit(0);
	}
}

/**
 * exec_args - Function to execute a process in child process
 * @parsed: string received
 * @env: Environment
 *
 * Return: No returns in this function
 */

void exec_args(char **parsed, char **env, paths_t *p_path_string)
{
	int process;
	pid_t pid;
	/**
	 * Forking a child
	 */
	func_exit(parsed, p_path_string);
	check_path(parsed, p_path_string);
	/*print_list(p_path_string);*/
	pid = fork();

	if (pid == -1)
	{
		printf("\nFailed fork in juanito :c..");
		return;
	}
	else if (pid == 0)
	{
		process = execve(parsed[0], parsed, env);
		printf("process %i : ", process);
		if (process < 0)
		{
			printf("Error juanito no process\n");
		}
		exit(0);
	}
	else
	{
		/**
		 * waiting for child to terminate
		 */
		wait(NULL);
		if (parsed)
			free_parsed(parsed);
	}
}

void parse_text_path(char *str, char **parsed)
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
	/*if (dest)
	  free(dest);*/
}

size_t print_list(paths_t *h)
{
	int counter = 0;

	if (!h)
		return (0);
	while (h)
	{
		if (h->path)
		{
			printf("%s\n", h->path);
			h = h->next;
		}
		else
		{
			printf("[0] %p\n", h->path);
			h = h->next;
		}
		counter++;
	}
	return (counter);
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
	char **tmp2 = (char **) malloc(sizeof(char) * 1024);
	paths_t *head;

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
	i = 0;
	head = NULL;
	while (tmp2[i])
	{
		create_struct(&head, tmp2[i]);
		i++;
	}
	free(tmp2);
	/*print_list(head);*/
	return (head);
}

/**
 * sigintHandler - Function to anulate the ^C
 * Description: There's no parameters inside this function
 *
 * Return: No returns in this function
 */

void sigintHandler(int nt)
{
	(void)nt;
	printf("\n$(╯°□°）╯");
	fflush(stdout);
}

/**
 * command_promt - Function to open a prompt for our shell
 * @envp: Receive the arguments passed to shell
 *
 * Return: No returns in this function
 */

void command_promt(char *envp[])
{
	/*int size_juanito = 1024;*/
	/*char *input_user;*/
	char **parsed_args;
	ssize_t bytes_read;
	size_t nbytes = 0;
	char *buffer;
	paths_t *p_path_string;
	char *path;

	p_path_string = NULL;
		/*(paths_t *)malloc(sizeof(paths_t));*/
	path = "PATH";
	p_path_string = get_path(envp, path);

	/**
	 * char cwd[1024];
	 * char *username;
	 * username = getlogin();
	 * getcwd(cwd, sizeof(cwd));
	 */

	signal(SIGINT, sigintHandler);
	while (1)
	{
		if (isatty(0))
			printf("$(╯°□°）╯ ");
		buffer = NULL;
		/*input_user = (char *)malloc(size_juanito);
		if (input_user == NULL)
		exit(0);*/
		parsed_args = (char **)malloc(sizeof(char) * 1024);
		parsed_args[1] = NULL;/*   "Aparentemente esto "soluciona el problema""*/
		/*printf("parsed[1]: %s\n", parsed_args[1]);
		if (parsed_args == NULL)
		exit(0);*/
		bytes_read = getline(&buffer, &nbytes, stdin);
		if (bytes_read == -1)
		{
			free(buffer);
			free_list(p_path_string);
			/*free(p_path_string);*/
			free(parsed_args);
			/*free(input_user);*/
			printf("You can't kill JUANITO!!!\n");
			/**
			 * this line need to be commented
			 */
			exit(0);
		}
		if (buffer[0] != '\n')
		{
			/*input_user = buffer;*/
			/*_strcpy(input_user, buffer);    "ESTO NUNCA
			  if (buffer)                  FUE NECESARIO :)"
			  free(buffer);*/
			parse_text(buffer, parsed_args);
			exec_args(parsed_args, envp, p_path_string);
		}
		free(buffer);
		/*if (parsed_args)
			free_parsed(parsed_args);*/
		/*if (input_user)*/ /*funciona ... a veces*/
		/*free(input_user);*/
	}
	free(buffer);
	if (p_path_string)
	{
		free_list(p_path_string);
		free(p_path_string);
	}
}

/**
 * main - Entry Point
 * @ac: counter of arguments
 * @av: arguments received in shell
 * @envp: environment
 *
 * Return: Always 0 (success)
 */

int main(int ac, char **av, char *envp[])
{
	(void)ac;
	(void)av;
	command_promt(envp);

	return (0);
}
