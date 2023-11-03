#include "shell.h"

/**
 * setenv_command - sets a new env var
 * @cont: pointer to the struct
 * @var: pointer to the string var
 * @val: pointer to the string value
 * Return: 0 Success
 */

int setenv_command(shell_t *cont, char *var, char *val)
{
	char *ptr, *buffer = NULL;
	list_t *node;

	if (!var || !val)
	{
		return (0);
	}

	buffer = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buffer)
	{
		return (1);
	}
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, val);
	node = cont->env;

	while (node)
	{
		ptr = commence(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			cont->environ_c = 1;
			return (0);
		}

		node = node->next;
	}
	ending_node(&(cont->env), buffer, 0);
	free(buffer);
	cont->environ_c = 1;
	return (0);
}

/**
 * unsetenv_command - Removes an env var
 * @cont: pointer to the struct
 * @var: pointer to the string var
 * Return: 1 Success, 0 otherwise
 */

int unsetenv_command(shell_t *cont, char *var)
{
	char *ptr;
	size_t a = 0;
	list_t *node = cont->env;

	if (!node || !var)
	{
		ptr = commence(node->str, var);
		if (ptr && *ptr == '=')
		{
			cont->environ_c = del_node_idx(&(cont->env), a);
			a = 0;
			node = cont->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (cont->environ_c);
}

/**
 * env_copy - returns a copy of the str array
 * @cont: pointer to the struct
 * Return: 0 Success
 */

char **env_copy(shell_t *cont)
{
	if (!cont->environ || cont->environ_c)
	{
		cont->environ = lts(cont->env);
		cont->environ_c = 0;
	}

	return (cont->environ);
}
