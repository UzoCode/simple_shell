#include <stdio.h>
#include <unistd.h>

/**
 *main - example of fork
 *
 *Return: Always 0.
 */
int main(void)
{
	pid_t call_pid;
	pid_t childs_pid;
	pid_t parents_pid;
	pid_t pid;

	pid = fork();

	if (pid == -1)
	{
		perror("Error:");
		return (1);
	}

	if (pid == 0)
	{
		printf("After fork\n");

		childs_pid = getpid();
		call_pid = getppid();

		printf("childs pid is %u\n", childs_pid);
		printf("process pid is %u\n", call_pid);
	}
	else
	{
		printf("before fork\n");

		call_pid = getpid();
		parents_pid = getppid();

		printf("process is %u\n", call_pid);
		printf("bash pid(parents) is %u\n", parents_pid);
	}

	return (0);
}
