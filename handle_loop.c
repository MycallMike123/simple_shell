#include "shell.h"

/**
 *  hsh - the loop
 *  @cont: pointer to the struct
 *  @argv: The arg vector
 *  Return: 0 success, 0 otherwise
 */

int hsh(shell_t *cont, char **argv)
{
	int bi;
	ssize_t _read = 0;

	bi = 0;
	while (_read != -1 && bi != -2)
	{
		handle_clear_info(cont);
		if (interactive(cont))
			_puts("$ ");
		print_char(BUF_FLUSH);

		_read = get_line(cont);
		if (_read != -1)
		{
			handle_info(cont, argv);
			handling_builtin = find_b(cont);
			if (handling_builtin == -1)
				find_command(cont);
		}

		else if (interactive(cont))
			_putchar('\n');
		release_info(cont, 0);
	}
	create_history(cont);
	release_info(cont, 1);
	if (!interactive(cont) && cont->process)
		exit(cont->process);
	if (handling_builtin == -2)
	{
		if (cont->number_error == -1)
		{
			exit(cont->process);
		}
		exit(cont->number_error);
	}

	return (handling_builtin);
}

/**
 * command_fork - forks
 * @cont: pointer to the struct
 */

void command_fork(shell_t *cont)
{
	pid_t s_pid = fork();

	if (s_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (s_pid == 0)
	{
		if (execve(cont->path, cont->argv, env_copy(cont)) == -1)
		{
			release_info(cont, 1);
			if (errno == EACCES)
			{
				exit(126);
			}
			exit(1);
		}
	}
	else
	{
		wait(&(cont->process));
		if (WIFEXITED(cont->process))
		{
			cont->process = WEXITSTATUS(cont->process);
			if (cont->process == 126)
			{
				print_err(cont, "Permission denied\n");
			}
		}
	}
}

/**
 * find_command - finds a command
 * @cont: pointer to the struct
 */

void find_command(shell_t *cont)
{
	int a, b;
	char *path = NULL;

	cont->path = cont->argv[0];

	if (cont->lcf == 1)
	{
		cont->lc++;
		cont->lcf = 0;
	}

	for (a = 0, b = 0; cont->arg[a]; a++)
	{
		if (!_delimeter(cont->arg[a], " \t\n"))
			b++;
	}
	if (!b)
		return;

	path = handle_find_path(cont, getenv_command(cont, "PATH="), cont->argv[0]);
	if (path)
	{
		cont->path = path;
		command_fork(cont);
	}
	else
	{
		if ((interactive(cont) || getenv_command(cont, "PATH=")
					|| cont->argv[0][0] == '/') && handle_command(cont, cont->argv[0]))
			command_fork(cont);
		else if (*(cont->arg) != '\n')
		{
			cont->process = 127;
			print_err(cont, "not found\n");
		}
	}
}

/**
 * find_b - finds the builtin cmd
 * @cont: pointer to the struct
 * Return: 0 success, -1, 1, 2 otherwise
 */

int find_b(shell_t *cont)
{
	int a, handling_bi = -1;
	bi_t bi[] = {
		{"exit", handle_exit},
		{"env", handle_env},
		{"help", process_cd},
		{"history", handle_hist},
		{"setenv", new_env},
		{"unsetenv", remove_env},
		{"cd", handle_change_directory},
		{"alias", handle_alias},
		{NULL, NULL}
	};

	for (a = 0; bi[a].type; a++)
	{
		if (_strcmp(cont->argv[0], bi[a].type) == 0)
		{
			cont->lc++;
			handling_bi = bi[a].fn(cont);
			break;
		}
	}
	return (handling_bi);
}
