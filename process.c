#include "shell.h"

/**
 * pid - identify process ID
 * Return: Always 0
 */
int pid(void)
{
	pid_t pid;

	pid = getpid();
	printf("%u\n", pid);
	return (0);
}

/**
 * ppid - identify parent process ID
 * Return: Always 0
 */
int ppid(void)
{
	pid_t ppid;

	ppid = getppid();
	printf("%u\n", ppid);
	return (0);
}
