#include "shell.h"

/**
 * tokenize - to tokenizes input then stores in an array
 *@input_strings: inputs to be parsed
 *@delims: delimiter used, just one character string
 *
 *Return: array of the tokens
 */

char **tokenize(char *input_strings, char *delims)
{
	int num_delims = 0;
	char **av = NULL;
	char *tokens = NULL;
	char *save_ptrs = NULL;

	tokens = _strtok_s(input_strings, delims, &save_ptrs);

	while (tokens != NULL)
	{
		av = _reallocs(av, sizeof(*av) * num_delims, sizeof(*av) * (num_delims + 1));
		av[num_delims] = tokens;
		tokens = _strtok_s(NULL, delims, &save_ptrs);
		num_delims++;
	}

	av = _reallocs(av, sizeof(*av) * num_delims, sizeof(*av) * (num_delims + 1));
	av[num_delims] = NULL;

	return (av);
}

/**
 *prints - prints strings to stdout
 *@strings: string that will be printed
 *@streams: stream that is print out to
 *
 *Return: void, return nothing
 */
void prints(char *strings, int streams)
{
	int i = 0;

	for (; strings[i] != '\0'; i++)
		write(streams, &strings[i], 1);
}

/**
 *removes_newlines - dismisses new line from a string
 *@strs: string to be used
 *
 *Return: void
 */

void removes_newlines(char *strs)
{
	int i = 0;

	while (strs[i] != '\0')
	{
		if (strs[i] == '\n')
			break;
		i++;
	}
	strs[i] = '\0';
}

/**
 *_strcpys - copies string to another buffer
 *@sources: source to copy from
 *@desti: destination to copy to
 *
 * Return: void
 */

void _strcpys(char *sources, char *desti)
{
	int i = 0;

	for (; sources[i] != '\0'; i++)
		desti[i] = sources[i];
	desti[i] = '\0';
}

/**
 *_strlens - counts the string length
 *@strings: string that will be counted
 *
 * Return: the string length
 */

int _strlens(char *strings)
{
	int lens = 0;

	if (strings == NULL)
		return (lens);
	for (; strings[lens] != '\0'; lens++)
		;
	return (lens);
}
