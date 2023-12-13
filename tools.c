#include "shell.h"

/**
 * Auth: Akosa Benedict
 * 		 Makinwa Joseph
 *
 * Description: main.c extended functions
 */


/** parse_commands - defines the type of the command
 * @commands: commands that are parsed
 *
 * Return: represents sepcific type of the commands
 * Description -
 * 		 EXTERNAL_COMMAND (1) represents commands as /bin/ls
 *		 INTERNAL_COMMAND (2) represents commands as exit, env
 *		 PATH_COMMAND (3) represents commands seen in PATH as ls
 *		 INVALID_COMMAND (-1) represents invalid commands
 */

int parse_commands(char *commands)
{
	int i;
	char *internal_commands[] = {"env", "exit", NULL};
	char *paths = NULL;

	for (i = 0; commands[i] != '\0'; i++)
	{
		if (commands[i] == '/')
			return (EXTERNAL_COMMAND);
	}
	for (i = 0; internal_commands[i] != NULL; i++)
	{
		if (_strcmp(commands, internal_commands[i]) == 0)
			return (INTERNAL_COMMAND);
	}
	/* @checks_paths - checks if command is in the PATH */
	paths = checks_paths(commands);
	if (paths != NULL)
	{
		free(paths);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * execute_commands - executes command based on type
 * @tokenize_commands: form of the command tokenized(ls -l == {ls, -l, NULL})
 * @commands_types: the command type
 *
 * Return: void
 */
void execute_commands(char **tokenize_commands, int commands_types)
{
	void (*func)(char **commands);

	if (commands_types == EXTERNAL_COMMAND)
	{
		if (execve(tokenize_commands[0], tokenize_commands, NULL) == -1)
		{
			perror(_getenvs("PWD"));
			exit(2);
		}
	}
	if (commands_types == PATH_COMMAND)
	{
		if (execve(checks_paths(tokenize_commands[0]), tokenize_commands, NULL) == -1)
		{
			perror(_getenvs("PWD"));
			exit(2);
		}
	}
	if (commands_types == INTERNAL_COMMAND)
	{
		func = get_funcs(tokenize_commands[0]);
		func(tokenize_commands);
	}
	if (commands_types == INVALID_COMMAND)
	{
		print(shell_names, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tokenize_commands[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		statue = 127;
	}
}

/**
 * checks_paths - checks if command is in PATH
 * @commands: command to be used
 *
 * Return: path where the command is found, NULL if not found
 */
char *checks_paths(char *commands)
{
	char **path_arrays = NULL;
	char *temps, *temps2, *paths_cpy;
	char *paths = _getenvs("PATH");
	int i;

	if (paths == NULL || _strlens(paths) == 0)
		return (NULL);
	paths_cpy = malloc(sizeof(*paths_cpy) * (_strlens(paths) + 1));
	_strcpy(paths, paths_cpy);
	path_arrays = tokenizer(paths_cpy, ":");
	for (i = 0; path_arrays[i] != NULL; i++)
	{
		temps2 = _strcat(path_arrays[i], "/");
		temps = _strcat(temp2, commands);
		if (access(temps, F_OK) == 0)
		{
			free(temps2);
			free(path_arrays);
			free(paths_cpy);
			return (temps);
		}
		free(temps);
		free(temps2);
	}
	free(paths_cpy);
	free(path_arrays);
	return (NULL);
}

/**
 * get_funcs - retrieves functions based on given command given and mapping
 * @commands: string that check against mapping
 *
 * Return: pointer to proper function, or NULL on fail
 */
void (*get_funcs(char *commands))(char **)
{
	int i;
	functions_maps mappings[] = {
		{"env", env}, {"exit", quit}
	};

	for (i = 0; i < 2; i++)
	{
		if (_strcmps(commands, mappings[i].command_names) == 0)
			return (mappings[i].funcs);
	}
	return (NULL);
}

/**
 * _getenvs - defines value of an environment variable
 * @names: name of environment variable
 *
 * Return: value of variable as string
 */
char *_getenvs(char *names)
{
	char **my_environs;
	char *pair_ptrs;
	char *names_cpy;

	for (my_environs = environ; *my_environs != NULL; my_environs++)
	{
		for (pair_ptrs = *my_environs, names_cpy = names;
		     *pair_ptrs == *names_cpy; pair_ptrs++, names_cpy++)
		{
			if (*pair_ptrs == '=')
				break;
		}
		if ((*pair_ptrs == '=') && (*names_cpy == '\0'))
			return (pair_ptrs + 1);
	}
	return (NULL);
}
