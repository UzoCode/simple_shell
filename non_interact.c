#include "shell.h"

/**
 * non_interacting - handles all non_interactive mode
 *
 * Return: void
 */

void non_interacting(void)
{
	char **recent_commands = NULL;
	int i, types_commands = 0;
	size_t n = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&lines, &n, stdin) != -1)
		{
			remove_newlines(lines);
			remove_comments(lines);
			command = tokenize(lines, ";");
			for (i = 0; command[i] != NULL; i++)
			{
				recent_commands = tokenize(command[i], " ");
				if (recent_commands[0] == NULL)
				{
					free(recent_commands);
					break;
				}
				types_commands = parse_commands(recent_commands[0]);
				initialize(recent_commands, types_commands);
				free(recent_commands);
			}
			free(command);
		}
		free(lines);
		exit(statue);
	}
}
