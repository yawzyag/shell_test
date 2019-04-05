#include <stdio.h>

void enviroment(char **env)
{
    while(*env)
        printf("%s\n",*env++);
	
}

int main(int argc, char *argv[], char *envp[])
{
	enviroment(envp);
	return (0);
}
