#include "shell.h"

/**
 * ffree - frees a string
 * @str: pointer to pointer to the string
 */

void ffree(char **str)
{
	char **p = str;

	if (!str)
	{
		return;
	}

	while (str)
	{
		free(*str++);
	}

	free(p);
}

/**
 * _realloc - Reallocates a memory block
 * @ptr: A pointer to the previous mem allocation
 * @old_size: The size of the old memory block in bytes
 * @new_size: The new size in bytes
 * Return: A pointer to the reallocated memory block, NULL otherwise
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *pointer;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		pointer = malloc(new_size);
		if (pointer == NULL)
		{
			return (NULL);
		}
		return (pointer);
	}
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	pointer = malloc(new_size);

	if (pointer == NULL)
	{
		return (NULL);
	}
	if (new_size < old_size)
	{
		old_size = new_size;
	}

	memcpy(pointer, ptr, old_size);
	free(ptr);

	return (pointer);
}

/**
 * _memset - Fills memory with a constant byte
 * @s: Pointer to the memory area
 * @b: The constant byte to fill the memory with
 * @n: The number of bytes to fill
 * Return: A pointer to the memory area @s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
	{
		s[a] = b;
	}

	return (s);
}

/**
 * commence - checks if needle starts with haystack
 * @hay: The string to search
 * @needle: pointer to the substring to find
 * Return: address of next char, NULL otherwise
 */

char *commence(const char *hay, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *hay++)
		{
			return (NULL);
		}
	}
	return ((char *)hay);
}

/**
 * _strlen - Computes the length of a string
 * @s: Pointer to the string
 * Return: Length of the string
 */

int _strlen(char *s)
{
	int len = 0;

	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}
