#include "shell.h"

/**
 * main - the main entry point of the program
 * @argc: The arguments count
 * @argv: The argument vector
 * Return: 0 Success, 1 otherwise
 */

int main(int argc, char **argv)
{
	int file_descriptor = 2;
	shell_t cont[] = { INFO_INIT };

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_descriptor)
			: "r" (file_descriptor));

	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY);

		if (file_descriptor == -1)
		{
			if (errno == EACCES)
			{
				exit(126);
			}

			if (errno == ENOENT)
			{
				input_str(argv[0]);
				input_str(": 0: Can't open ");
				input_str(argv[1]);
				print_char('\n');
				print_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		cont->read_file_descriptor = file_descriptor;
	}

	locate_env(cont);
	handle_read_history(cont);
	hsh(cont, argv);
	return (EXIT_SUCCESS);
}

/**
 * handle_command - determines if a file is an exec command
 * @cont: pointer to the struct
 * @path: path to the file
 * Return: 1 success, 0 otherwise
 */

int handle_command(shell_t *cont, char *path)
{
	struct stat _stat;

	(void)cont;

	if (!path || stat(path, &_stat))
	{
		return (0);
	}

	if (_stat.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 * handle_find_path - finds the command in the path str
 * @cont: pointer to the struct
 * @_path: pointer to the path str
 * @cmd: pointer to the command to find
 * Return: path, NULL otherwise
 */

char *handle_find_path(shell_t *cont, char *_path, char *cmd)
{
	int a = 0, current = 0;
	char *path;

	if (!_path)
		return (NULL);
	if ((_strlen(cmd) > 2) && commence(cmd, "./"))
	{
		if (handle_command(cont, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!_path[a] || _path[a] == ':')
		{
			path = duplicate_char(_path, current, a);
			if (!*path)
			{
				_strcat(path, cmd);
			}

			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			if (handle_command(cont, path))
			{
				return (path);
			}
			if (!_path[a])
				break;

			current = a;
		}
		a++;
	}

	return (NULL);
}

/**
 * duplicate_char - duplicates chars
 * @_path: pointer to the path str
 * @st_idx: The startin' index
 * @sp_idx: the stoppin' idx
 * Return: the new buf
 */

char *duplicate_char(char *_path, int st_idx, int sp_idx)
{
	static char buf[1024];
	int a, b;

	a = 0;
	b = 0;

	for (b = 0, a = st_idx; a < sp_idx; b++)
	{
		if (_path[a] != ':')
		{
			buf[b++] = _path[a];
		}
	}
	buf[b] = 0;

	return (buf);
}

/**
 * _free -  frees a pointer
 * @p: address of the pointer to free
 * Return: 1 success, 0 otherwise
 */

int _free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
