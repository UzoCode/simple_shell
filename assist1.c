#include "shell.h"

/**
 * fork - fork example
 *
 * Return: Always 0
 */
int fork(void)
{
	pid_t process_pid;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return (1);
	}

	process_pid = getpid();
	printf("My pid is %u\n", process_pid);

	if (pid == 0)
	{
		printf("(%u) Nooooo!\n", process_pid);
	}
	else
	{
		printf("(%u) %u, I am your Godfather\n", process_pid, pid);
	}

	return (0);
}
