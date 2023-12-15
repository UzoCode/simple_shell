#include "shell.h"

void prompts();
char **split_strings(char *str, const char *delim);
void freestr_array(char **str_ptr);

/**
 * main - point of entry
 * Return: 0 success, 1 failure
 */
int main(void)
{
	char *lines = NULL;
	size_t lens = 0;
	ssize_t reads;
	char **argv = NULL;

	prompts();
	while ((reads = getline(&lines, &lens, stdin)) != -1)
	{
		/*Print command entered*/
		printf("%s", lines);

		argv = split_strings(lines, " ");

		/*Print the next prompt*/
		prompts();
	}
	free(lines);
	freestr_array(argv);
	return (0);
}

/**
 * prompts - displays prompt
 * Return: None
 */
void prompts()
{
	printf("$ ");
	fflush(stdout);  /*displays prompt immediately*/
}

/**
 * split_strings - splits a string by the space delimiter
 * @str: string to split
 * @delim: character to split
 *
 * Return: array of each word of the string
 */
char **split_strings(char *str, const char *delim)
{
	char *token = NULL;
	char **array_tokens = malloc(sizeof(char *) * 1024);
	size_t u = 0, j = 0;

	token = strtok(str, delim);
	while (token != NULL)
	{
		array_tokens[u] = strdup(token);

		if (array_tokens[u] == NULL)
		{
			for (j = 0; j <= u; j++)
			{
				free(array_tokens[j]);
			}
			free(array_tokens);
			return (NULL);
		}


		token = strtok(NULL, delim);
		u++;
	}

	return (array_tokens);
}

/**
 * freestr_array - free array of strings
 * @str_ptr: pointer to strings
 */
void freestr_array(char **str_ptr)
{
	size_t u = 0;

	while (str_ptr[u] != NULL)
	{
		free(str_ptr[u]);
		u++;
	}
	free(str_ptr);
}
