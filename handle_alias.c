#include "shell.h"

/**
 * handle_alias - creates an alias
 * @cont: A pointer to the struct
 * Return: 0 success
 */

int handle_alias(shell_t *cont)
{
	int a;
	char *ptr = NULL;
	list_t *node = NULL;

	if (cont->argc == 1)
	{
		node = cont->alias;
		while (node)
		{
			alias_print(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; cont->argv[a]; a++)
	{
		ptr = _strchr(cont->argv[a], '=');

		if (ptr)
		{
			alias_set(cont, cont->argv[a]);
		}

		else
		{
			alias_print(start_node(cont->alias, cont->argv[a], '='));
		}
	}
	return (0);
}

/**
 * alias_set - sets alias to string
 * @cont: A pointer to the struct
 * @str: pointer to the string
 * Return: 0 success, 1 otherwise
 */

int alias_set(shell_t *cont, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');

	if (!ptr)
	{
		return (1);
	}

	if (!*++ptr)
	{
		return (handle_unset_alias(cont, str));
	}

	handle_unset_alias(cont, str);

	return (ending_node(&(cont->alias), str, 0) == NULL);
}

/**
 * handle_unset_alias - sets alias to string
 * @cont: A pointer to the struct
 * @str: pointer to the string
 * Return: 0 success, 1 otherwise
 */

int handle_unset_alias(shell_t *cont, char *str)
{
	char *ptr;
	char a;
	int b;

	ptr = _strchr(str, '=');
	if (!ptr)
	{
		return (1);
	}

	a = *ptr;
	*ptr = 0;
	b = del_node_idx(&(cont->alias),
			getnode_idx(cont->alias, start_node(cont->alias, str, -1)));

	*ptr = a;

	return (b);
}

/**
 * alias_print - prints alias
 * @node: the alias node
 * Return: 0 success, 1 otherwise
 */

int alias_print(list_t *node)
{
	char *ptr, *c;

	ptr = NULL;
	c = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');

		for (c = node->str; c <= ptr; c++)
		{
			_putchar(*c);
			_putchar('\'');
			_puts(ptr + 1);
			_puts("'\n");
			return (0);
		}
	}

	return (1);
}

/**
 * handle_hist - displays the history list
 * @cont: pointer to the struct
 * Return: 0 success
 */

int handle_hist(shell_t *cont)
{
	list_print(cont->history);

	return (0);
}
