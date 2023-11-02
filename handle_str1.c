#include "shell.h"

/**
 * _strcmp - Compares two strings
 * @s1: The first string to be compared
 * @s2: The second string
 * Return: An integer less than, equal to, or greater than
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * _strcat - Concatenates two strings
 * @dest: The destination string
 * @src: The source string to be appended
 * Return: A pointer to the resulting string destination
 */

char *_strcat(char *dest, char *src)
{
	char *dest_pointer = dest;

	while (*dest_pointer != '\0')
	{
		dest_pointer++;
	}

	while (*src != '\0')
	{
		*dest_pointer = *src;
		dest_pointer++;
		src++;
	}

	*dest_pointer = '\0';
	return (dest);
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 */

void _puts(char *str)
{
	int a = 0;

	if (!str)
	{
		return;
	}

	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}

/**
 * _strcpy - Copies a string from src to dest
 * @dest: Pointer to the destination buffer
 * @src: Pointer to the source strg
 * Return: Pointer to the destination buffer
 */

char *_strcpy(char *dest, char *src)
{
	int a = 0;

	while (src[a] != '\0')
	{
		dest[a] = src[a];
		a++;
	}

	dest[a] = '\0';

	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: pointer to the string to duplicat
 * Return: pointer to the duplicated string
 */

char *_strdup(const char *str)
{
	int len = 0;
	char *p;

	if (str == NULL)
	{
		return (NULL);
	}

	while (*str++)
	{
		len++;
	}

	p = malloc(sizeof(char) * (len + 1));

	if (!p)
	{
		return (NULL);
	}

	for (len++; len--;)
	{
		p[len] = *--str;
	}

	return (p);
}
