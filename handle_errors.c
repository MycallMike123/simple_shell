#include "shell.h"

/**
 * input_file_descriptor - writes the character to file_descriptor
 * @c: The character to print
 * @file_descriptor: The fd to write
 * Return: 1 success, -1 otherwise
 */

int input_file_descriptor(char c, int file_descriptor)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(file_descriptor, buf, a);
		a = 0;
	}

	if (c != BUF_FLUSH)
	{
		buf[a++] = c;
	}

	return (1);
}

/**
 * input_fd_string - Prints a string
 * @s: the string to be printed
 * @file_descriptor: The fd to write
 * Return: No of chars
 */

int input_fd_string(char *s, int file_descriptor)
{
	int a;

	a = 0;
	if (!s)
	{
		return (0);
	}
	while (*s)
	{
		a += input_file_descriptor(*s++, file_descriptor);
	}

	return (a);
}

/**
 * print_char - writes the xter c to stderr
 * @c: The character to print
 * Return: 0 success, -1 otherwise
 */

int print_char(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}

	if (c != BUF_FLUSH)
	{
		buf[a++] = c;
	}
	return (1);
}

/**
 * input_str - prints an input str
 * @s: the string to print
 */

void input_str(char *s)
{
	int a;

	a = 0;
	if (!s)
	{
		return;
	}

	while (s[a] != '\0')
	{
		print_char(s[a]);
		a++;
	}
}

/**
 * convert_error - converts a string to an integer
 * @s: the string to be converted
 * Return: No of converted strings, -1 otherwise
 */

int convert_error(char *s)
{
	int a;
	unsigned long int res = 0;

	a = 0;

	if (*s == '+')
	{
		s++;
	}

	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			res *= 10;
			res += (s[a] - '0');

			if (res > INT_MAX)
			{
				return (-1);
			}
		}

		else
		{
			return (-1);
		}
	}

	return (res);
}
