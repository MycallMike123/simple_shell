#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: The destination string
 * @src: source string to be copied
 * @n: The maximum number of characters to be copied
 * Return: A pointer to the resulting string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int k;

	for (k = 0; k < n && src[k] != '\0'; k++)
		dest[k] = src[k];

	while (k < n)
	{
		dest[k] = '\0';
		k++;
	}

	return (dest);
}

/**
 * _strncat - Concatenates two strings with a limit on bytes
 * @dest: The destination string
 * @src: The source string
 * @n: The maximum number of bytes
 * Return: A pointer to the resulting string destination
 */

char *_strncat(char *dest, char *src, int n)
{
	char *dest_pointer = dest;

	while (*dest_pointer != '\0')
	{
		dest_pointer++;
	}

	while (*src != '\0' && n > 0)
	{
		*dest_pointer = *src;
		dest_pointer++;
		src++;
		n--;
	}

	*dest_pointer = '\0';

	return (dest);
}

/**
 * _delimeter - checks if a xter is a delimeter
 * @s: character to check
 * @del: the delimeter string
 * Return: 1 success, 0 otherwise
 */

int _delimeter(char s, char *del)
{
	while (*del)
	{
		if (*del++ == s)
		{
			return (1);
		}
	}

	return (0);
}

/**
 * _isalpha - Checks if a character is an alphabetic letter
 * @s: The character to check
 * Return: 1 if alphabetic, 0 otherwise
 */

int _isalpha(int s)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * str_to_int - Converts a string to an integer
 * @s: Pointer to the string to be converted
 * Return: The converted integer
 */

int str_to_int(char *s)
{
	int a, o;
	int sign = 1, fl = 0;
	unsigned int res = 0;

	for (a = 0; s[a] != '\0' && fl != 2; a++)
	{
		if (s[a] == '-')
		{
			sign *= -1;
		}

		if (s[a] >= '0' && s[a] <= '9')
		{
			fl = 1;
			res *= 10;
			res += (s[a] - '\0');
		}

		else if (fl == 1)
		{
			fl = 2;
		}
	}

	if (sign == -1)
	{
		o = -res;
	}
	else
	{
		o = res;
	}

	return (o);
}
