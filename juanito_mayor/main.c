#include "shell.h"

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
