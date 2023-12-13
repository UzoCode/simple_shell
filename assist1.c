#include "shell.h"

/**
 *_strcmps - for comparing two strings
 *@one: first string compared
 *@two: second string compared
 *
 * Return: difference in both strings
 */

int _strcmps(char *one, char *two)
{
	int i = 0;

	while (one[i] != '\0')
	{
		if (one[i] != two[i])
			break;
		i++;
	}
	return (one[i] - two[i]);
}

/**
 *_strcats - for concatenating two strings
 *@final: string concatenated to
 *@sources: string to be concatenated
 *
 * Return: new string address
 */

char *_strcats(char *final, char *sources)
{
	char *new_strings =  NULL;
	int len_fina = _strlens(final);
	int len_sources = _strlens(sources);

	new_strings = malloc(sizeof(*new_strings) * (len_fina + len_sources + 1));
	_strcpys(final, new_strings);
	_strcpys(sources, new_strings + len_fina);
	new_strings[len_fina + len_sources] = '\0';
	return (new_strings);
}

/**
 *_strspns - gets length of prefix substring
 *@strs1: string searched
 *@strs2: string used
 *
 *Return: number of bytes in initial segment of 5 part of accept
 */

int _strspns(char *strs1, char *strs2)
{
	int i = 0;
	int matches = 0;

	while (strs1[i] != '\0')
	{
		if (_strchrs(strs2, strs1[i]) == NULL)
			break;
		matches++;
		i++;
	}
	return (matches);
}

/**
 *_strcspns - computes segment of strs1 consisting of characters not in strs2
 *@strs1: string searched
 *@strs2: string used
 *
 *Return: index where char in strs1 exists in strs2
 */


int _strcspns(char *strs1, char *strs2)
{
	int lens = 0, i;

	for (i = 0; strs1[i] != '\0'; i++)
	{
		if (_strchrs(strs2, strs1[i]) != NULL)
			break;
		lens++;
	}
	return (lens);
}

/**
 *_strchrs - for locating char in string
 *@se: string searched
 *@ch: char checked
 *
 *Return: pointer to the first occurence of c in s
 */

char *_strchrs(char *se, char ch)
{
	int i = 0;

	for (; se[i] != ch && se[i] != '\0'; i++)
		;
	if (se[i] == ch)
		return (se + i);
	else
		return (NULL);
}
