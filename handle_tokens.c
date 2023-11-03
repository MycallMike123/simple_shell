#include "shell.h"

/**
 * strtow - splits a string into words
 * @str: the input string
 * @delim: the delimeter string
 * Return: a pointer to an array of strings, NULL otherwise
 */

char **strtow(char *str, char *delim)
{
	int a, b, c, d, count = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!_delimeter(str[a], delim) &&
				(_delimeter(str[a + 1], delim) || !str[a + 1]))
			count++;

	if (count == 0)
		return (NULL);

	s = malloc((1 + count) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < count; b++)
	{
		while (_delimeter(str[a], delim))
			a++;
		c = 0;
		while (!_delimeter(str[a + c], delim) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));

		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = str[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}
