#include "shell.h"

	char **command = NULL;
	char *lines = NULL;
	char *shell_names = NULL;
	int statue = 0;

/**
 * main - main shell coded
 * @argc: number of passed arguments
 * @argv: list of program arguments to be parsed
 *
 * and applies functions of Tools and assists
 * implements EOF
 * Prints error when it Fails
 * Return: 0 on success
 */


int main(int argc __attribute__((unused)), char **argv)
{
	char **recent_command = NULL;
	int i, types_commands = 0;
	size_t n = 0;

	signal(SIGINT, ctrl_c_handler);
	shell_names = argv[0];
	while (1)
	{
		non_interacting();
		print(" ($) ", STDOUT_FILENO);
		if (getline(&lines, &n, stdin) == -1)
		{
			free(lines);
			exit(statue);
		}
			removes_newlines(lines);
			removes_comments(lines);
			command = tokenizer(lines, ";");

		for (i = 0; command[i] != NULL; i++)
		{
			recent_command = tokenizer(command[i], " ");
			if (recent_command[0] == NULL)
			{
				free(recent_command);
				break;
			}
			types_commands = parse_commands(recent_command[0]);

			/* initializers -   */
			initializer(recent_command, types_commands);
			free(recent_command);
		}
		free(command);
	}
	free(lines);

	return (statue);
}
