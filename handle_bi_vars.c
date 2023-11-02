#include "shell.h"

/**
 * string_substitute - replaces string
 * @old: address of old string
 * @_new: address of the new string
 * Return: 1 success
 */

int string_substitute(char **old, char *_new)
{
	free(*old);
	*old = _new;
	return (1);
}

/**
 * alias_substitute - replaces an aliases
 * @cont: pointer to the struct
 * Return: 1 Success
 */

int alias_substitute(shell_t *cont)
{
	int a;
	char *ptr;
	list_t *node;

	for (a = 0; a < 10; a++)
	{
		node = start_node(cont->alias, cont->argv[0], '=');
		if (!node)
		{
			return (0);
		}

		free(cont->argv[0]);

		ptr = _strchr(node->str, '=');
		if (!ptr)
		{
			return (0);
		}

		ptr = _strdup(ptr + 1);
		if (!ptr)
		{
			return (0);
		}
		cont->argv[0] = ptr;
	}

	return (1);
}

/**
 * chain_check - Checks if a buf is chain delim
 * @cont: pointer to the struct
 * @buf: pointer to the char buffer
 * @ptr: address of current position
 *  Return: 1 Success, 0 otherwise
 */

int chain_check(shell_t *cont, char *buf, size_t *ptr)
{
	size_t b = *ptr;

	if (buf[b] == '|' && buf[b + 1] == '|')
	{
		buf[b] = 0;
		b++;
		cont->command_buffer_type = CMD_OR;
	}

	else if (buf[b] == '&' && buf[b + 1] == '&')
	{
		buf[b] = 0;
		b++;
		cont->command_buffer_type = CMD_AND;
	}

	else if (buf[b] == ';')
	{
		buf[b] = 0;
		cont->command_buffer_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}

	*ptr = b;

	return (1);
}

/**
 * handle_chain - checks chaining based on last status
 * @cont: pointer to the struct
 * @buf: pointer to the char buffer
 * @ptr: address of current position
 * @a: starting position in the buffer
 * @len: length of the buf
 */

void handle_chain(shell_t *cont, char *buf, size_t *ptr, size_t a, size_t len)
{
	size_t b = *ptr;

	if (cont->command_buffer_type == CMD_AND)
	{
		if (cont->process)
		{
			buf[a] = 0;
			b = len;
		}
	}

	if (cont->command_buffer_type == CMD_OR)
	{
		if (!cont->process)
		{
			buf[a] = 0;
			b = len;
		}
	}

	*ptr = b;
}

/**
 * var_substitute - replaces variables
 * @cont: pointer to the struct
 * Return: 1 success, 0 otherwise
 */

int var_substitute(shell_t *cont)
{
	int a;
	list_t *node;

	a = 0;
	for (a = 0; cont->argv[a]; a++)
	{
		if (cont->argv[a][0] != '$' || !cont->argv[a][1])
		{
			continue;
		}

		if (!_strcmp(cont->argv[a], "$?"))
		{
			string_substitute(&(cont->argv[a]),
					_strdup(convert_num(cont->process, 10, 0)));
			continue;
		}

		if (!_strcmp(cont->argv[a], "$$"))
		{
			string_substitute(&(cont->argv[a]), _strdup(convert_num(getpid(), 10, 0)));
			continue;
		}

		node = start_node(cont->env, &cont->argv[a][1], '=');
		if (node)
		{
			string_substitute(&(cont->argv[a]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}

		string_substitute(&cont->argv[a], _strdup(""));
	}

	return (0);
}
