#include "shell.h"

/**
 * execute_commands - executes a command with full path
 * @command: full path
 *
 * Return: 0 on success, 1 on failure
 */
void execute_commands(const char *commands)
{
	pid_t child_pid;
	int status;
	char *argv[] = {"command", NULL};

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		/* This code runs in the child process*/
		if (execve(command, argv, NULL) == -1)
		{
			perror("exec error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/*This runs in the parent process*/
		wait(&status);
	}
}

int main(void)
{
	char *lines = NULL;
	size_t lens = 0;
	ssize_t read_lens;

	while (1)
	{
		printf("SS-Shell> ");
		fflush(stdout);

		read_lens = getline(&lines, &lens, stdin);
		if (read_lens == -1)
		{
			perror("getline error");
			exit(EXIT_FAILURE);
		}

		/*Remove the newline character if present*/
		if (lines[read_lens - 1] == '\n')
		{
			lines[read_lens - 1] = '\0';
		}

		execute_commands(lines);
	}

	return (0);
}
