#include "shell.h"

/**
 * handle_signals - handle signals
 * @sigint: the signal number
 */
void handle_signals(int sigint)
{
	prompts(sigint);
	if (sigint == 2)
	{
		errno = 130;
	}
}

/**
 * main - the entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 success
 */
int main(int argc, char **argv)
{
	signal(SIGINT, handle_signals);

	if (argc > 1)
	{
		exit(execute_commands_from_files(argv));
	}

	while (prompts(0))
	{
		argc = get_argv(&argv);
		if (argc > 0)
		{
			argv[argc] = NULL;
			run_commands(argv);
			free_argv(argv);
		}
	}
	return (0);
}

/**
 * exit_with_errors - writes message to stderr exits with error code
 * @code: error code
 * @shell: shell program
 * @filename: file name
 */
void exit_with_errors(int code, char *shell, const char *filename)
{
	dprintf(STDERR_FILENO, "%s: 0: Can't open %s\n", shell, filename);
	exit(code);
}


/**
 * execute_commands_from_files - commands execute from a file
 * @argv: argument vector
 *
 * Description: Reads commands from specified file and execute
 *
 * Return: 0 if successful, -1 on error
 *
 */
int execute_commands_from_files(char **argv)
{
	char command[1000];
	int fds;
	ssize_t bytes_read;

	if (access(argv[1], R_OK) != 0)
		exit_with_errors(127, argv[0], argv[1]);

	fds = open(argv[1], O_RDONLY);
	if (fds == -1)
	{
		perror((char *)EACCES);
		exit(127);
	}

	while ((bytes_read = read(fds, command, sizeof(command))) > 0)
	{
		pid_t child_p = fork();

		if (child_p == -1)
		{
			perror("Error creating process");
			return (1);
		}

		if (child_p == 0)
		{
			char *args[] = {"/bin/sh", "-c", NULL, NULL};

			command[bytes_read] = '\0';
			args[2] = command;

			if (execve(args[0], args, environ) == -1)
			{
				perror("execve error");
			}
		}
	}

	close(fds), exit(0);
	return (0);
}

/**
 * run_commands - function that directs execution flow
 * @argv: argument vector
 *
 * Return: 0 if succesful and -1 if unsuccessful
 */
int run_commands(char **argv)
{
	get_builtin execute_builtin;
	int run_statuss;

	execute_builtin = handle_builtin_func(argv[0]);
	if (execute_builtin)
		run_statuss = execute_builtin(argv);
	else
		run_statuss = execute_command(argv);

	return (run_statuss);
}
