#include "shell.h"

/**
 * handle_env - handles and prints the current environment
 * @cont: The pointer to the struct
 * Return: 0 Success
 */

int handle_env(shell_t *cont)
{
	string_list(cont->env);

	return (0);
}

/**
 * locate_env - locates the env linked list
 * @cont: The pointer to the struct
 * Return: 0 Success
 */

int locate_env(shell_t *cont)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
	{
		ending_node(&node, environ[a], 0);
	}

	cont->env = node;

	return (0);
}

/**
 * getenv_command - gets the value of an environ var
 * @cont: The pointer to the struct
 * @nam: pointer to ther environ var name
 * Return: value
 */

char *getenv_command(shell_t *cont, const char *nam)
{
	char *ptr;
	list_t *node = cont->env;

	while (node)
	{
		ptr = commence(node->str, nam);

		if (ptr && *ptr)
		{
			return (ptr);
		}

		node = node->next;
	}
	return (NULL);
}

/**
 * new_env - starts a new environment
 * @cont: The pointer to the struct
 * Return: 1 Success, 0 otherwise
 */

int new_env(shell_t *cont)
{
	if (cont->argc != 3)
	{
		input_str("Incorrect number of arguements\n");

		return (1);
	}

	if (setenv_command(cont, cont->argv[1], cont->argv[2]))
	{
		return (0);
	}

	return (1);
}

/**
 * remove_env - removes an env var
 * @cont: The pointer to the struct
 * Return: 0 Success, 1 otherwise
 */

int remove_env(shell_t *cont)
{
	int a;

	if (cont->argc == 1)
	{
		input_str("Too few arguements.\n");
		return (1);
	}

	for (a = 1; a <= cont->argc; a++)
	{
		unsetenv_command(cont, cont->argv[a]);
	}

	return (0);
}

