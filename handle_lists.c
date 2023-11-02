#include "shell.h"

/**
 * handle_node - Adds a node at the start of the ls
 * @_start: pointer to the head node
 * @str: pointer to the string
 * @num: the node index
 * Return: The size of the new_node
 */

list_t *handle_node(list_t **_start, const char *str, int num)
{
	list_t *new;

	if (!_start)
	{
		return (NULL);
	}

	new = malloc(sizeof(list_t));

	if (!new)
	{
		return (NULL);
	}

	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}

	new->next = *_start;
	*_start = new;

	return (new);
}

/**
 * ending_node - Adds a node at the end of the ls
 * @_start: pointer to the head node
 * @str: pointer to the string
 * @num: the node index
 * Return: The size of the new_node
 */

list_t *ending_node(list_t **_start, const char *str, int num)
{
	list_t *node, *new;

	if (!_start)
	{
		return (NULL);
	}

	node = *_start;
	new = malloc(sizeof(list_t));
	if (!new)
	{
		return (NULL);
	}

	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;

	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
		{
			node = node->next;
		}
		node->next = new;
	}
	else
	{
		*_start = new;
	}
	return (new);
}

/**
 * getnode_idx - gets a node's idx
 * @_start: pointer to the head node
 * @node: pointer to the node
 * Return: node's idx, -1 otherwise
 */

ssize_t getnode_idx(list_t *_start, list_t *node)
{
	size_t a = 0;

	while (_start)
	{
		if (_start == node)
		{
			return (a);
		}

		_start = _start->next;
		a++;
	}

	return (-1);
}

/**
 * start_node - return nodes that start with a prefix
 * @node: pointer to the node
 * @pref: string to to check
 * @c: the next xter after the prefix to match
 * Return: The node, NULL otherwise
 */

list_t *start_node(list_t *node, char *pref, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = commence(node->str, pref);
		if (ptr && ((c == -1) || (*ptr == c)))
		{
			return (node);
		}

		node = node->next;
	}

	return (NULL);
}

/**
 * del_node_idx - deletes node at a given idx
 * @_start: pointer to the head node
 * @idx: index of node to delete
 * Return: 1 success, 0 otherwise
 */

int del_node_idx(list_t **_start, unsigned int idx)
{
	unsigned int a;
	list_t *node, *prev_node;

	a = 0;
	if (!_start || !*_start)
	{
		return (0);
	}

	if (!idx)
	{
		node = *_start;
		*_start = (*_start)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *_start;

	while (node)
	{
		if (a == idx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}
