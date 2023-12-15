#include "shell.h"

/**
 * main - a stat sample
 *
 * Return: Always 0 success
 */
int main(int ac, char **av)
{
	unsigned int u;
	struct stat file;

	if (ac < 2)
	{
		printf("Usage: %s path_to_file ...\n", av[0]);
		return (1);
	}
	u = 1;
	while (av[u])
	{
		printf("%s:", av[u]);
		if (stat(av[u], &file) == 0)
		{
			printf(" FOUND\n");
		}
		else
		{
			printf(" NOT FOUND\n");
		}
		u++;
	}
	return (0);
}
