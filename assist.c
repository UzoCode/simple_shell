#include "shell.h"

/**
 * main - Entry point of the program
 * @argc: argument number
 * @argv: argument vector
 * Return: 0 success, 1 if fail
 */
int main(int argc, char *argv[])
{
	const char *pathname = argv[1];
	const char *paths = getenv("PATH");
	char *path_cpy, *token;
	char real_paths[1024];

	if ((argc != 2) || (paths == NULL))
	{
		perror("Error:");
		return (1);
	}

	path_cpy = strdup(paths);
	if (!path_cpy)
	{
		perror("Error:");
		return (1);
	}

	token = strtok(path_cpy, ":");
	while (token)
	{
		/* concatenate token found in PATH with the file passed*/
		snprintf(real_paths, sizeof(real_paths), "%s/%s", token, pathname);

		if (access(real_paths, F_OK) == 0)
		{
			printf("%s\n", real_paths);
			free(path_cpy);
			return (0);
		}
		token = strtok(NULL, ":");
	}

	free(path_cpy);
	return (1);
}
