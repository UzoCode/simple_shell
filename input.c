#include "shell.h"

/**
 * _input - accepts user input and tokenize string
 *
 * Return: Void
 */
int _input(void)
{
	int counter = 0;
	char *input = NULL;
	size_t bufsize = 0;
	size_t returnedbyte = 0;
	char *token = NULL;
	char **args = malloc(10 * sizeof(char *));
	
	returnedbyte = getline(&input, &bufsize, stdin);
	token = strtok(input, " ");
	while(token != NULL)
	{
		args[counter]= malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(args[counter], token);
		counter++;
		token = strtok(NULL, " ");
	}
	args[counter] = NULL;

	for (int num = 1; num < counter; num++)
	{
		printf("%d: %s\n", num, args[num]);
	}
}
