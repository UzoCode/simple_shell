#include "shell.h"

/**
 * creates_new_env - forms a new environment variable
 * @name: variable name
 * @value: the variable value
 *
 * Return: 0 if successful
 */
int creates_new_env(char *name, char *value)
{
	char **new_environ;
	char **new_env_ptr, **env_ptr;
	size_t new_variable_len = _strlen(name) + _strlen(value) + 2;
	/* +2 is added for '=' and '\0'*/
	char *new_variable = malloc(new_variable_len);

	if (name == NULL || value == NULL)
	{
		perror("No variable name or value found");
		return (-1);
	}
	if (new_variable == NULL)
	{
		perror("Failed to allocate memory");
		return (-ENOMEM);
	}
	new_variable = _strcats(new_variable, name, value, '=');

	/*find the number of variable in environ*/
	env_ptr = environ;
	while (*env_ptr)
		env_ptr++;

	new_environ = malloc((env_ptr - environ + 2) * sizeof(char *));
	if (new_environ == NULL)
	{
		perror("Failed to allocate memory"), free(new_variable);
		return (-ENOMEM);
	}
	/*copy existing environ into new environ*/
	new_env_ptr = new_environ;
	env_ptr = environ;
	while (*env_ptr)
		*new_env_ptr++ = *env_ptr++;

	*new_env_ptr++ = new_variable;
	*new_env_ptr = NULL;
	/* replace old envrionment with new environment*/
	environ = new_environ;
	return (0);
}

/**
 * _setenvs -  changes or adds an environment variable
 * @name: name of variable
 * @value: value of variable
 * @overwrite: integer to modify environment
 *
 * Return: 0 if successful
 */
int _setenvs(char *name, char *value, int overwrite)
{
	size_t name_len = _strlen(name);
	/* +2 is added for '=' and '\0'*/
	size_t new_variable_len = name_len + _strlen(value) + 2;
	char **env_ptr = environ;

	if (!overwrite)
		return (0); /*variable exist and overwrite is not allowed*/

	while (*env_ptr)
	{
		/* check if existing variable match name*/
		if (_strncmps(*env_ptr, name, name_len) == 0 &&
		    ((*env_ptr)[name_len] == '='))
		{
			char *new_variable = malloc(new_variable_len);

			if (new_variable == NULL)
			{
				perror("Failed to allocate memory");
				return (-1);
			}

			/**
			 * TODO:
			 * If variable exists, unset variable
			 * before setting a new one
			 */
			new_variable = _strcats(new_variable, name, value, '=');
			/*replace old variable with new variable*/
			*env_ptr = new_variable;

			free(new_variable);
			return (0);
		}
		env_ptr++;
	}
	/*if the variable does not exist*/
	return (creates_new_env(name, value));
}

/**
 * _unsetenvs - removes an environment variable
 * @name: name of variable
 *
 * Return: 0 if successful
 */
int _unsetenvs(char *name)
{
	char **env_ptr;
	char **next_env_ptr;
	size_t name_len = _strlen(name);

	if (name == NULL)
	{
		perror("Invalid argument");
		return (-1);
	}
	env_ptr = environ;
	while (*env_ptr)
	{
		/* find environment variable to remove*/
		if (_strncmps(*env_ptr, name, name_len) == 0 && ((*env_ptr)[name_len] == '='))
		{
			free(*env_ptr);

			/*move the remaining variables up the array*/
			next_env_ptr = env_ptr + 1;
			while (*next_env_ptr)
				*env_ptr++ = *next_env_ptr++;

			*env_ptr = NULL;

			return (0);
		}
		env_ptr++;
	}

	return (-1); /*variable not found*/
}

/**
 * _getenvs - gets an environment variable.
 * @name: variable name.
 *
 * Return: pointer to value in environment or NUll if not found.
 */
char *_getenvs(const char *name)
{
	char **environ_copy;
	char *current_var;
	unsigned int length = _strlen(name);

	environ_copy = environ;
	while (*environ_copy != NULL)
	{
		current_var = *environ_copy;

		/*checks if the current VAR matches name*/
		if ((_strncmps(current_var, name, length) == 0) &&
		    (current_var[length] == '='))
		{
			return (current_var + length + 1);
			/*+1 is added to skip the '=' char*/
		}

		environ_copy++;
	}

	return (NULL);

}

/**
 * creates_env_table - creates environment variables
 * @envp: array of strings
 *
 * Return: array of strings containing environment variables.
 */

char **creates_env_table(char **envp)
{
	/*Count the number of environment variables*/
	int count = 0, u;
	char **env;

	while (envp[count] != NULL)
		count++;

	/* Allocate memory for the array of environment variables*/
	env = (char **)malloc((count + 1) * sizeof(char *));
	if (env == NULL)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	memset(env, 0, (count + 1));

	/* Copy each environment variable to the new array*/
	for (u = 0; u < count; u++)
	{
		env[u] = _strdup(envp[u]);
		if (env[u] == NULL)
		{
			perror("Memory allocation failed");
			exit(1);
		}
	}
	/* Add a NULL terminator to the end of the array*/
	env[count] = NULL;

	return (env);
}
