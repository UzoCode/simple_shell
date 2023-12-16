#include "shell.h"

/**
 * execute_commands - executes command with arguments
 * @argv: command array and arguments
 *
 * Return: 0 on success, 1 on failure
 */
int execute_commands(char **argv)
{
	char *cmd_path = argv[0];
	pid_t child_pid;
	size_t ishandlepath = 0;

	if (access(cmd_path, X_OK) != 0)
	{
		cmd_path = handle_paths(cmd_path);
		ishandlepath = 1;
	}
	if (cmd_path == NULL)
	{
		perror("Command not found");
		return (-1);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork error");
		return (-1);
	}
	if (child_pid == 0)
	{
		char *envp[] = {NULL};

		if (execve(cmd_path, argv, envp) == -1)
		{
			perror("execve error");
		}
	}
	else
	{
		int status;

		wait(&status);
	}

	if (ishandlepath)
		free(cmd_path);

	return (0);
}

/**
 * handle_paths - returns command fullpath
 * @cmd: the command passed
 *
 * Return: command fullpath passed
 */
char *handle_paths(char *cmd)
{
	char *path = _getenv("PATH");
	char *path_copy;
	char *token;
	char *full_path;
	size_t full_path_len = 0;

	path_copy = _strdup(path);
	if ((path == NULL) || (path_copy == NULL))
	{
		perror("PATH not found");
		return (NULL);
	}

	token = strtok(path_copy, ":");
	full_path_len = _strlen(token) + _strlen(cmd) + 2;
	full_path = malloc(sizeof(char) * full_path_len);
	while (token)
	{
		/*concatenate the token in PATH with the command passed*/
		full_path = _strcat(full_path, token, cmd, '/');

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
