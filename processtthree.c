#include "shell.h"

/**
 * main - Process ID
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t my_pid;

	my_pid = getpid();
	printf("The Child process id: %u\n", my_pid);

	my_pid = getppid();
	printf("The Parent process id: %u\n", my_pid);

	return (0);
}
