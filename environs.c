#include "shell.h"

/**
 * main - prints env and environ environment and addresses
 * @ac: argument count
 * @av: argument vector
 * @env: environment variable
 * Return: 0 success
 */
int main(int ac, char **av, char **env)
{
	unsigned int u = 0;
	extern char **environ;
	(void)ac;
	(void)av;

	while (env[u] != NULL)
	{
		printf("%s\n", env[u]);
		u++;
	}

	printf("env address is: %p\n", env);
	printf("environ address is: %p\n", environ);
	return (0);
}
