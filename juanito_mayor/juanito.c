#include "shell.h"
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

	if (parsed != NULL)
	{
		/*for (i = 0; parsed[i];)
		    {
		      i++;
		        }
			  i - 1;
			    for (; i != 0; i--)
			      {
			        if (parsed[i])
				  free(parsed[i]);
				    }
				      if (parsed[0])
				      free(parsed[0]);*/
		if (parsed)
			free(parsed);
	}
}

/**
 * takeInput - Function to take the input and copy it.
 * @str: Copy of the string inside the function
 * @buffer: String inside the buffer to be copied
 *
 * Return: always 1 if success, in other case 0
 */

int takeInput(char *str, char *buffer)
{
	if (_strlen(buffer) != 0)
	{
		strcpy(str, buffer);
		return (0);
	}
	else
	{
		return (1);
	}
}

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
		parsed[i] = _strdup(dest);
		dest = strtok(NULL, delimiters);
		i++;
	}
	if(str)
		free(str);
	if (dest)
		free(dest);
}

void check_path(char **parsed, const paths_t *h)
{
	char *tmp = malloc(sizeof(char) * 1024);
	char *tmp2 = malloc(sizeof(char) * 1024);
	char *juanito = malloc(sizeof(char) * 1024);
	struct stat *buf;

	if(_strlen(parsed[0]) < 9)
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
				if(stat(tmp2, buf) == 0)
				{
					parsed[0] = _strdup(tmp2);
					break;
				}
				h = h->next;
			}
		}
	}
	if(juanito)
		free(juanito);
	if(tmp)
		free(tmp);
	if(tmp2)
		free(tmp2);
}

/**
 * check_parse - Function to check the commands words
 * @parsed: string parsed where you can find a command word
 *
 * Return: No returns in this function
 */

void check_parse(char **parsed)
{
	if (strcmp(parsed[0], "exit") == 0)
	{
		if (parsed[1])
		{
			if (atoi(parsed[1]))
				exit(atoi(parsed[1]));
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

void exec_args(char **parsed, char **env, const paths_t *p_path_string)
{
	int process;
	pid_t pid;
	/**
	 * Forking a child
	 */
	check_parse(parsed);
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
		parsed[i] = _strdup(dest);
		dest = strtok(NULL, delimiters);
		i++;
	}
	if (dest)
		free(dest);
}

size_t print_list(const paths_t *h)
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
	paths_t *new_node = (paths_t *) malloc(sizeof(paths_t));

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
	char **tmp2 = malloc(sizeof(char *) * 1024);
	paths_t *head;

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
	parse_text_path(tmp, tmp2);
	i = 0;
	head = NULL;
	while(tmp2[i])
	{
		create_struct(&head, tmp2[i]);
		i++;
	}
	/*print_list(head);*/
	return(head);
}

/**
 * command_promt - Function to open a prompt for our shell
 * @envp: Receive the arguments passed to shell
 *
 * Return: No returns in this function
 */

void command_promt(char *envp[])
{
	int size_juanito = 1024;
	char *input_user;
	char **parsed_args;
	ssize_t bytes_read;
	size_t nbytes = 0;
	char *buffer;

	paths_t *p_path_string = malloc(sizeof(char) * 1024);
	char *path;

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
		buffer = malloc(sizeof(char) * size_juanito);
		bytes_read = getline(&buffer, &nbytes, stdin);
		input_user = malloc(sizeof(char) * size_juanito);
		parsed_args = malloc(sizeof(char *) * size_juanito);
		if (bytes_read == -1)
		{
			printf("You can't kill JUANITO!!!\n");
/**
 * this line need to be commented
 */
			exit(98);
		}
		if (buffer[0] != '\n')
		{
			takeInput(input_user, buffer);
			if (buffer)
				free(buffer);
			parse_text(input_user, parsed_args);
			exec_args(parsed_args, envp, p_path_string);
		}
	}
	free_list(p_path_string);
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
