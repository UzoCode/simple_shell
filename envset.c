#include "shell.h"

/**
 * _setenv_news - add new environment variable
 * @names: name of variable
 * @values: value of variable
 *
 * Return: 0 if successful
 */
int _setenv_news(const char *names, const char *values)
{
	extern char **environs;
	char **new_environs;
	char **new_env_ptrs, **env_ptrs;
	size_t new_variable_lens = strlen(names) + strlen(values) + 2;
	/* +2 is added for '=' and '\0'*/
	char *new_variables = malloc(new_variable_lens);

	if (new_variables == NULL)
	{
		perror("Failed to allocate memory");
		return (-1);
	}
	snprintf(new_variables, new_variable_lens, "%s=%s", names, values);

	/*finds number of variable in environ*/
	env_ptrs = environs;
	while (*env_ptrs)
		env_ptrs++;

	new_environs = malloc((env_ptrs - environs + 2) * sizeof(char *));
	/* "(env_ptr - environ)" calculate number of variables
	in environment and +2 is for the new variable and NULL*/
	if (new_environs == NULL)
	{
		perror("Allocate memory failed");
		free(new_variables);
		return (-1);
	}
	/*copy existing environ into new environ*/
	new_env_ptrs = new_environs;
	env_ptrs = environs;
	while (*env_ptrs)
		*new_env_ptrs++ = *env_ptrs++;

	*new_env_ptrs++ = new_variables;
	*new_env_ptrs = NULL;
	/* replace old envrionment with new environment*/
	environs = new_environs;

	return (0);
}

/**
 * _setenvs -  change or add environment variable
 * @names: name of variable
 * @values: value of variable
 * @overwrites: integer to modify environment
 *
 * Return: 0 if successful
 */
int _setenvs(const char *names, const char *values, int overwrites)
{
	extern char **environs;
	char *new_variables;
	size_t name_lens = strlen(name);
	size_t new_variable_lens = name_lens + strlen(values) + 2;
	/* +2 is added for '=' and '\0'*/

	char **env_ptrs = environs;

	while (*env_ptrs)
	{
		/* check if existing variable match name*/
		if (strncmp(*env_ptrs, names, name_lens) == 0 && ((*env_ptrs)[name_lens] == '='))
		{
			if (overwrites)
			{
				new_variables = malloc(new_variable_lens);
				if (new_variables == NULL)
				{
					perror("Failed to allocate memory");
					return (-1);
				}
				snprintf(new_variables, new_variable_lens, "%s=%s", names, values);
				/*replace old variable with new variable*/
				free(*env_ptrs);
				*env_ptrs = new_variables;

				free(new_variables);
				return (0);
			}
			else
				return (0); /*variable exist and overwrite is not allowed*/
		}
		env_ptrs++;
	}
	/*if the variable does not exist*/
	return (_setenv_new(names, values));
}

/**
 * _unsetenvs - removes an environment variable
 * @names: name of variable
 *
 * Return: 0 if successful
 */
int _unsetenvs(const char *names)
{
	extern char **environs;
	char **env_ptrs;
	char **next_env_ptrs;
	size_t name_lens = strlen(names);

	if (names == NULL)
	{
		perror("Invalid argument");
		return (-1);
	}
	env_ptrs = environs;
	while (*env_ptrs)
	{
		/* find environment variable to remove*/
		if (strncmp(*env_ptrs, names, name_lens) == 0 && ((*env_ptrs)[name_lens] == '='))
		{
			free(*env_ptrs);

			/*moves remaining variables up the array*/
			next_env_ptrs = env_ptrs + 1;

			while (*next_env_ptrs)
				*env_ptrs++ = *next_env_ptrs++;

			*env_ptrs = NULL;

			return (0);
		}
		env_ptrs++;
	}

	return (0); /*variable not found*/
}

int main(void)
{
	char *my_vars;
	if (_setenv("MY_VARIABLE", "hello world", 1) == 0)
	{
		printf("variable successfully added\n");
	}
	else
		printf("variable unsuccessful\n");
	my_vars = getenv("MY_VARIABLE");

	if (my_vars != NULL)
		printf("value of my_vars = %s\n", my_vars);
	else
		printf("my_vars not found\n");

	if (_unsetenv("MY_VARIABLE") == 0)
		printf("MY_VARIABLE unset successfully\n");
	else
		printf("failed to unset MY_VARIABLE");

	return (0);
}
