#include "shell.h"

/**
 * _strlen  - calculate length of a string
 * @str: strings
 *
 * Return: the string length
 */
size_t _strlen(const char *str)
{
	size_t lengths = 0;

	while (str[lengths] != '\0')
	{
		lengths++;
	}
	return (lengths);
}

/**
 * _strchr - searches first occurrence of character in a string
 * @strs: strings
 * @characters: the ascii character
 *
 * Return: pointer to character within the string
 */
char *_strchr(const char *strs, int characters)
{
	while (*strs != '\0')
	{
		if (*strs == characters)
		{
			return ((char *)strs);
		}
		strs++;
	}
	return (NULL);
}

/**
 * _strtok - split string into substrings
 * using delimiter character
 * @str: the string
 * @delim: delimeter
 *
 * Return: substrings (token)
 */
char *_strtok(char *str, const char *delim)
{
	static char *lastTokens;
	char *endOfTokens = NULL;
	char *token = NULL;

	if (str != NULL)
		lastTokens = str;

	if (lastTokens == NULL)
		return (NULL);

	token = lastTokens;
	while (*token != '\0' && _strchr(delim, *token) != NULL)
	{
		token++;
	}

	if (*token == '\0')
	{
		lastTokens = NULL;
		return (NULL);
	}

	endOfTokens = token + 1;
	while (*endOfTokens != '\0' && _strchr(delim, *endOfTokens) == NULL)
	{
		endOfTokens++;
	}

	*endOfTokens = '\0';
	lastTokens = endOfTokens + 1;

	return (token);
}

/**
 * _strcpy - copies string from source to destination
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to the start of destination string
 */
char *_strcpy(char *dest, const char *src)
{
	/*Save starting point of dest address*/
	char *dest_starts = dest;

	/*Copy char from src to dest*/
	while ((*dest++ = *src++))
		;

	return (dest_starts);
}

/**
 * _strdup - duplicates given string
 * @str: string
 *
 * Return: new dynamically allocated copy of the string
*/
char *_strdup(const char *str)
{
	size_t lens = _strlen(str);
	char *duplicates;

	if (str == NULL)
		return (NULL);

	duplicates = malloc(sizeof(char *) * lens + 1);
	if (duplicates == NULL)
		return (NULL);
	_strcpy(duplicates, str);

	return (duplicates);
}
