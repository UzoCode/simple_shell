#include "shell.h"

/**
 *_strtok_s - tokenizes string
 *@strings: string that will be tokenized
 *@delims: delimiter used to tokenize string
 *@save_ptrs: pointer for keeping track of the next token
 *
 *Return: The next available token
 */
char *_strtok_s(char *strings, char *delims, char **save_ptrs)
{
	char *finishes;

	if (strings == NULL)
		strings = *save_ptrs;

	if (*strings == '\0')
	{
		*save_ptrs = strings;
		return (NULL);
	}

	strings += _strspns(strings, delims);
	if (*strings == '\0')
	{
		*save_ptrs = strings;
		return (NULL);
	}

	finishes = strings + _strcspns(strings, delims);
	if (*finishes == '\0')
	{
		*save_ptrs = finishes;
		return (strings);
	}

	*finishes = '\0';
	*save_ptrs = finishes + 1;
	return (strings);
}

/**
 * _atoi_i - change string to integer
 * @s: the string to be changed
 *
 * Return: the converted int
 */
int _atoi_i(char *u)
{
	unsigned int n = 0;

	do {
		if (*u == '-')
			return (-1);
		else if ((*u < '0' || *u > '9') && *u != '\0')
			return (-1);
		else if (*u >= '0'  && *u <= '9')
			n = (n * 10) + (*u - '0');
		else if (n > 0)
			break;
	} while (*u++);
	return (n);
}

/**
 * _reallocs - reallocates memory block
 * @ptrs: points to memory previously allocated with malloc call
 * @old_sizes: size of ptr
 * @new_sizes: size of the new memory allocated
 *
 * Return: pointer to new memeory block address
 */
void *_reallocs(void *ptrs, unsigned int old_sizes, unsigned int new_sizes)
{
	void *temp_blocks;
	unsigned int i;

	if (ptrs == NULL)
	{
		temp_blocks = malloc(new_sizes);
		return (temp_blocks);
	}
	else if (new_sizes == old_sizes)
		return (ptrs);
	else if (new_sizes == 0 && ptrs != NULL)
	{
		free(ptrs);
		return (NULL);
	}
	else
	{
		temp_blocks = malloc(new_sizes);
		if (temp_blocks != NULL)
		{
			for (i = 0; i < min(old_sizes, new_sizes); i++)
				*((char *)temp_blocks + i) = *((char *)ptrs + i);
			free(ptrs);
			return (temp_blocks);
		}
		else
			return (NULL);

	}
}

/**
 * ctrl_c_handle - handles CTRL-C signal
 * @signums: the signal number
 *
 * Return: void
 */
void ctrl_c_handl(int signums)
{
	if (signums == SIGINT)
		print("\n($) ", STDIN_FILENO);
}

/**
 * removes_comments - removes/ignores all character '#'
 * @inputs: input to be used
 *
 * Return: void
 */
void removes_comments(char *inputs)
{
	int i = 0;

	if (inputs[i] == '#')
		inputs[i] = '\0';
	while (inputs[i] != '\0')
	{
		if (inputs[i] == '#' && inputs[i - 1] == ' ')
			break;
		i++;
	}
	inputs[i] = '\0';
}
