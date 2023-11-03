#include "shell.h"

/**
 * string_list - prints a list of strings only
 * @p: pointer to first node
 * Return: the listsize
 */

size_t string_list(const list_t *p)
{
	size_t a;

	a = 0;
	while (p)
	{
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		a++;
	}

	return (a);
}

/**
 * handle_freelist - frees all nodes of a list
 * @_start: pointer to pointer to head node
 */

void handle_freelist(list_t **_start)
{
	list_t *nxt_node, *head_node, *node;

	if (!_start || !*_start)
	{
		return;
	}

	head_node = *_start;
	node = head_node;

	while (node)
	{
		nxt_node = node->next;
		free(node->str);
		free(node);
		node = nxt_node;
	}
	*_start = NULL;
}

/**
 * list_print - prints all elements of a linked list
 * @p: pointer to first node
 * Return: the list size
 */

size_t list_print(const list_t *p)
{
	size_t a = 0;

	while (p)
	{
		_puts(convert_num(p->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		a++;
	}

	return (a);
}

/**
 * handle_list_length - determines the len of linked list
 * @p: pointer to the first node
 * Return: the list size
 */

size_t handle_list_length(const list_t *p)
{
	size_t a;

	a = 0;
	while (p)
	{
		p = p->next;
		a++;
	}

	return (a);
}

/**
 * lts - returns an array of strings
 * @_start: pointer to first node
 * Return: an array of str
 */

char **lts(list_t *_start)
{
	char *str, **strings;
	list_t *node = _start;
	size_t a = handle_list_length(_start), b;

	if (!_start || !a)
	{
		return (NULL);
	}

	strings = malloc(sizeof(char *) * (a + 1));

	if (!strings)
	{
		return (NULL);
	}

	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
			{
				free(strings[b]);
			}
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strings[a] = str;
	}
	strings[a] = NULL;
	return (strings);
}
