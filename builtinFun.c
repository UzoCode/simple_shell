#include "shell.h"

/**
 * changes_working_dir - changes working directory
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int changes_working_dir(char **argv)
{
	char *path, old_dir[PATH_MAX], new_dir[PATH_MAX];

	if (argv[1] == NULL || _strcmps(argv[1], "~") == 0)
		path = _getenvs("HOME");
	else if (_strcmps(argv[1], "-") == 0)
		path = _getenvs("OLDPWD");
	else
		path = argv[1];

	if (access(path, X_OK) != 0)
		(path)
		    ? dprintf(STDERR_FILENO,
			      "./hsh: 1: cd: can't cd to %s\n", path)
		    : 0;

	/*Get old pwd*/
	if (getcwd(old_dir, sizeof(old_dir)) == NULL)
		return (-1);

	/*Change directory*/
	if (chdir(path) != 0)
		return (-1);

	/*Update old pwd*/
	if (_setenvs("OLDPWD", old_dir, 1) != 0)
		return (-1);

	/*Get new pwd*/
	if (getcwd(new_dir, sizeof(new_dir)) == NULL)
		return (-1);

	/*Update new pwd*/
	if (_setenvs("PWD", new_dir, 1) != 0)
		return (-1);

	return (0);
}

/**
 * printenv - prints an environment variable
 * @argv: argument vector
 *
 * Return: 0 if successful
 */
int printenv(char **argv)
{
	int u = 0;

	(void)argv;

	while (environ[u] != NULL)
	{
		printf("%s\n", environ[u]);
		u++;
	}

	return (0);
}

/**
 * exit_simple_shells - exit shell
 * @argv: argument vector
 *
 * Return: 0 on exit and status if exit code is given
 */
int exit_simple_shells(char **argv)
{
	char *exit_code = argv[1];

	if (!exit_code)
	{
		frees_argv(argv);
		exit(0);
	}
	else
	{
		int code = atoi(exit_code);

		frees_argv(argv);
		exit(code);
	}
	return (0);
}

/**
 * modifyenv - modifies current environment with setenv or unsetenv
 * @argv: argument vector
 *
 * Return: 0 if successful
 */
int modifyenv(char **argv)
{
	char *command = argv[0];
	int result;

	if (_strcmps(command, "setenv") == 0 &&
	    (argv[1] != NULL) && (argv[2] != NULL))
	{
		char *name = argv[1];
		char *value = argv[2];

		result = _setenvs(name, value, 1);

		return (result);
	}

	if (_strcmps(command, "unsetenv") == 0 && (argv[1] != NULL))
	{
		char *name = argv[1];

		result = _unsetenvs(name);

		return (result);
	}

	perror(": Environment not modified");
	return (-1);
}
