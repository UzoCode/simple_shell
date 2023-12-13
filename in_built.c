#include "shell.h"

/**
 *envs - to print the current_environnement
 *@tokenize_commands: command entered
 *
 *Return: void
 */

void envs(char **tokenize_commands __attribute__((unused)))
{
	int i;

	for (i = 0; environs[i] != NULL; i++)
	{
		print(environs[i], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

/**
 * quit - exits the shell
 * @tokenized_command: command entered
 *
 * Return: void
 */

void quit(char **tokenize_commands)
{
	int num_tokens = 0, args;

	for (; tokenize_commands[num_tokens] != NULL; num_tokens++)
		;
	if (num_tokens == 1)
	{
		free(tokenize_commands);
		free(lines);
		free(command);
		exit(statue);
	}
	else if (num_tokens == 2)
	{
		args = _atoi_i(tokenize_commands[1]);
		if (args == -1)
		{
			print(shell_names, STDERR_FILENO);
			print(": 1: exit: Invalid number: ", STDERR_FILENO);
			print(tokenize_commands[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			statue = 2;
		}
		else
		{
			free(lines);
			free(tokenize_commands);
			free(command);
			exit(args);
		}
	}
	else
		print("$: exit takes only one argument\n", STDERR_FILENO);
}
