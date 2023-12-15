#include "shell.h"

/**
 * _getenv - environment variable.
 * @names: the variable name.
 *
 * Return: pointer to environment value NUll if not found.
 */
char *_getenv(const char *names)
{
	extern char **environ;
	char **environ_copy;
	char *current_var;
	unsigned int len = strlen(names);


	environ_copy = environ;
	while (*environ_copy != NULL)
	{
		current_var = *environ_copy;

		/*verify if the current VAR matches name*/
		if ((strncmp(current_var, names, len) == 0) && (current_var[len] == '='))
		{
			return (current_var + len + 1);
			/*add +1 to skip the '=' char*/
		}

		environ_copy++;
	}

	return (NULL);
}

/**
 * main - it gets PATH of enviroment variable
 *
 * Return: 0 always success
 */
int main(void)
{
	const char *names = "PATH";
	char *values = _getenv(names);

	if (values != NULL)
		printf("%s= %s\n", names, values);
	else
		printf("The environment variable %s not found\n", names);

	return (0);
}
