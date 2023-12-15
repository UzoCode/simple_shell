#include "shell.h"

/**
 * processtwo - fork example
 *
 * Return: Always 0
 */
int processtwo(void)
{
	pid_t processs_pid;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return (1);
	}

	processs_pid = getpid();
	printf("This pid is %u\n", processs_pid);

	if (pid == 0)
	{
		printf("(%u) Noooo!\n", processs_pid);
	}
	else
	{
		printf("(%u) %u, Here is the father\n", processs_pid, pid);
	}

	return (0);
}
