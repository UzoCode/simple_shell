#include "shell.h"

/**
 * path_direct - prints directory in the environment variable
 * PATH, one directory per line.
 *
 * Return: 0 Always
 */
int path_direct(void)
{
	char *values = getenv("PATH");
	char *token;

	if (!values)
	{
		printf("The environment variable not found\n");
		return (1);
	}

	token = strtok(values, ":");
	while (token)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}

	return (0);
}

/**
 * main - to test code
 *
 * Return: always 0
 */
int main(void)
{
	path_direct();

	return (0);
}
