#include "shell.h"

/**
 * handle_info - initializes the struct
 * @cont: pointer to the struct
 * @argument_vector: pointer to the argument
 */

void handle_info(shell_t *cont, char **argument_vector)
{
	int a = 0;

	cont->file_name = argument_vector[0];

	if (cont->arg)
	{
		cont->argv = strtow(cont->arg, " \t");

		if (!cont->argv)
		{
			cont->argv = malloc(sizeof(char *) * 2);
			if (cont->argv)
			{
				cont->argv[0] = _strdup(cont->arg);
				cont->argv[1] = NULL;
			}
		}

		for (a = 0; cont->argv && cont->argv[a]; a++)
		{
			;
		}

		cont->argc = a;

		alias_substitute(cont);
		var_substitute(cont);
	}
}

/**
 * release_info - frees the struct
 * @cont: pointer to the struct
 * @i: var to free
 */

void release_info(shell_t *cont, int i)
{
	ffree(cont->argv);
	cont->argv = NULL;
	cont->path = NULL;

	if (i)
	{
		if (!cont->command_buffer)
			free(cont->arg);
		if (cont->env)
			handle_freelist(&(cont->env));
		if (cont->history)
			handle_freelist(&(cont->history));
		if (cont->alias)
			handle_freelist(&(cont->alias));
		ffree(cont->environ);
		cont->environ = NULL;

		bfree((void **)cont->command_buffer);
		if (cont->read_file_descriptor > 2)
		{
			close(cont->read_file_descriptor);
		}

		_putchar(BUF_FLUSH);
	}
}

/**
 * handle_clear_info - Initializes shell_t struct
 * @cont: pointer to the struct
 */

void handle_clear_info(shell_t *cont)
{
	cont->arg = NULL;
	cont->argv = NULL;
	cont->path = NULL;
	cont->argc = 0;
}
