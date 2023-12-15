#include "shell.h"

/**
 * struct PATH - the PATH directories
 * @directory: the PATH directory
 * @next: the link to next node in list.
 *
 * Description: linked list structure to enviroment "PATH" directories
 */
typedef struct PATH
{
	char *directory;
	struct PATH *next;
} PATH;

/**
 * buildpath_list -  builds a linked list of the PATH directories.
 *
 * Return: returns pointer to head of a linked list
 */
PATH *buildpath_list(void)
{
	PATH *head = NULL, *current_directory = NULL;
	char *token;
	char *values = getenv("PATH");
	PATH *new_directoryy;

	token = strtok(values, ":");
	while (token)
	{
		new_directoryy = malloc(sizeof(PATH));
		if (!new_directoryy)
			return (NULL);

		new_directoryy->directory = strdup(token);
		new_directoryy->next = NULL;

		if (!head)
		{
			head = new_directoryy;
			current_directory = new_directoryy;
		}
		else
		{
			current_directory->next = new_directoryy;
			current_directory = new_directoryy;
		}

		token = strtok(NULL, ":");
	}

	return (head);
}

/**
 * main - to test code
 *
 * Return: always 0
 */
int main(void)
{
	PATH *path_lists, *current;

	path_lists = buildpath_list();
	current = path_lists;

	while (current)
	{
		printf("%s\n", current->directory);
		current = current->next;
	}
	/*free path_list*/
	while (path_lists)
	{
		PATH *temp = path_lists;
		path_lists = path_lists->next;

		free(temp->directory);
		free(temp);
	}

	return (0);
}
