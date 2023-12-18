#include "shell.h"

/**
 * prompts - prompt display to output
 * @signum: signal number
 *
 * Return: 1
 */
int prompts(size_t signum)
{
	char *prompts = (!signum) ? "$ " : "\n$ ";
	size_t prompt_lens = _strlen(prompts);

	if (signum == 1)
		prompts = "> ";

	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, prompts, prompt_lens);
		fflush(stdout);
	}
	return (1);
}

/**
 * frees_argv - frees string array
 * @argv: pointer to string array
 */
void frees_argv(char **argv)
{
	size_t u = 0;

	if (argv == NULL)
		return;

	while (argv[u] != NULL)
	{
		free(argv[u++]);
	}
	free(argv);
}

/**
 * resizes_argv - Resize argv array by doubling its size
 * @argv: pointer to string array
 * @max_argc: size of argv
 *
 * Return: 0 success, 1 failure
 */
int resizes_argv(char ***argv, size_t *max_argc)
{
	char **new_argv;
	size_t new_size, u;
	*max_argc *= 2;

	new_size = *max_argc * sizeof(char *);
	new_argv = _reallocs(*argv, new_size);
	if (new_argv == NULL)
		return (-ENOMEM);

	/*Copy existing pointers to the new array*/
	for (u = 0; u < *max_argc / 2; u++)
	{
		new_argv[u] = (*argv)[u];
	}

	frees_argv(*argv);
	*argv = new_argv;

	return (0);
}

/**
 * trims - remove leading and trailing whitespace or quotes from string
 * @str: the string
 */
void trims(char **str)
{
	char *starts = *str;
	char *ends = *str + _strlen(*str) - 1;

	/*Find the index of the first non-whitespace character*/
	while (*starts && (*starts == ' ' || *starts == '"' || *starts == '\t'))
	{
		starts++;
	}

	/*Find the index of the last non-whitespace character*/
	while (ends > starts && (*ends == ' ' || *ends == '"' || *ends == '\t'))
	{
		ends--;
	}

	/*Null-terminate the trimmed string*/
	ends[1] = '\0';

	/*Update the pointer to the trimmed string*/
	*str = starts;
}
