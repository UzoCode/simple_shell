#include "shell.h"

/**
 * main - prints all arguments, without ac
 * @ac: the argument count
 * @av: the argument variables
 * Return: 0 success, 1 failure
 */
int main(int ac __attribute__((unused)), char **av)
{
	int u = 0;

	while (av[u] != NULL)
	{
		printf("%s ", av[u++]);
	}
	putchar('\n');

	return (0);
}
