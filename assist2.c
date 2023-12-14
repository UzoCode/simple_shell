#include "shell.h"

/**
 * assist - Entry point of the program
 *
 * Return: 0 success, 1 if fail
 */
int assist(int argc, char *argv[])
{
	const char *pathname = argv[1];
	const char *path = getenv("PATH");
	char *path_copy, *token;
	char real_path[1024];

	if ((argc != 2) || (path == NULL))
	{
		perror("Error:");
		return (1);
	}

	path_copy = strdup(path);
	if (!path_copy)
	{
		perror("Error:");
		return (1);
	}

	token = strtok(path_copy, ":");
	while (token)
	{
		/* concatenate the token found in PATH with the file passed*/
		snprintf(real_path, sizeof(real_path), "%s/%s", token, pathname);

		if (access(real_path, F_OK) == 0)
		{
			printf("%s\n", real_path);
			free(path_copy);
			return (0);
		}
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (1);
}
