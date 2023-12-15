/**
 * main - to fork and wait then execve
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t child_pid;
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	char *pathname = argv[0];
	char *envp[] = {NULL};
	int u = 0;
	int status;

	while (u < 5)
	{
		printf("%d\n", u++);
		child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork error");
			return (1);
		}

		if (child_pid == 0)
		{
			execve(pathname, argv, envp);

			/**
			 * print error message when execve fails
			 * and proceed to child process
			 */
			perror("execve error");
			return (1);
		}
		else
		{
			/*Calling process*/
			printf("child exited\n");
			wait(&status);
		}
	}

	return (0);
}
