#include "shell.h"

/**
 * handles_builtin_func - handles builtin function
 * @cmd: command to check if it's a builtin
 *
 * Return: builtin function, NULL if not exist
 */
int (*handles_builtin_func(char *cmd))(char **argv)
{
	builtin_t builtins[] = {
		{"exit", exit_simple_shell},
		{"printenv", printenv},
		{"env", printenv},
		{"setenv", modifyenv},
		{"unsetenv", modifyenv},
		{"cd", change_working_dir},
	};
	int u = 0;

	while (u < (int)(sizeof(builtins) / sizeof(builtins[u])))
	{
		if (_strcmp(cmd, builtins[u].name) == 0)
			return (builtins[u].func);
		u++;
	}
	return (NULL);
}
