#include "shell.h"

/**
 * main - use global variable environ to print environmental variable
 *
 * Return: 0 success.
 */
int main(void)
{
	unsigned int u;
	extern char **environ;

	for (u = 0; environ[u] != NULL; u++)
	{
		printf("%s\n", environ[u]);
	}
	return (0);
}
