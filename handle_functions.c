#include "shell.h"

int _putchar(char c);

/**
 * interactive - checks if shell is interactive
 * @cont: pointer to the struct
 * Return: 1 if interactive, 0 otherwise
 */

int interactive(shell_t *cont)
{
	return (isatty(STDIN_FILENO) && cont->read_str <= 2);
}

/**
 * handle_exit - Exits shell
 * @cont: pointer to the struct
 * Return: exit with a status
 */

int handle_exit(shell_t *cont)
{
	int check;

	if (cont->argv[1])
	{
		check = convert_error(cont->argv[1]);

		if (check == -1)
		{
			cont->process = 2;
			print_err(cont, "Illegal number: ");
			input_str(cont->argv[1]);
			print_char('\n');
			return (1);
		}

		cont->number_error = convert_error(cont->argv[1]);
		return (-2);
	}

	cont->number_error = -1;
	return (-2);
}

/**
 * process_cd - changes the current directory of the process
 * @cont: pointer to the struct
 * Return: 0 Success
 */

int process_cd(shell_t *cont)
{
	char **args;

	args = cont->argv;
	_puts("Function not yet implemented \n");

	if (0)
	{
		_puts(*args)
	}

	return (0);
}

/**
 * handle_change_directory - changes the current directory
 * @cont: pointer to the struct
 *  Return: 0 Success
 */

int handle_change_directory(shell_t *cont)
{
	char *dir, *c, buf[1024];
	int c_ret;

	c = getcwd(buf, 1024);
	if (!c)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!cont->argv[1])
	{
		dir = getenv_command(cont, "HOME=");
		if (!dir)
			c_ret = chdir((dir = getenv_command(cont, "PWD=")) ? dir : "/");
		else
			c_ret = chdir(dir);
	}

	else if (_strcmp(cont->argv[1], "-") == 0)
	{
		if (!getenv_command(cont, "OLDPWD="))
		{
			_puts(c);
			_putchar('\n');
			return (1);
		}
		_puts(getenv_command(cont, "OLDPWD=")), _putchar('\n');
		c_ret = chdir((dir = getenv_command(cont, "OLDPWD=")) ? dir : "/");
	}

	else
		c_ret = chdir(cont->argv[1]);

	if (c_ret == -1)
	{
		print_err(cont, "cannot cd to ");
		input_str(cont->argv[1]), print_char('\n');
	}

	else
	{
		setenv_command(cont, "OLDPWD", getenv_command(cont, "PWD="));
		setenv_command(cont, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * _putchar - this writes the character to stdout
 * @c: the character to print
 * Return: 1 (Success)
 * On error, -1 is returned, and errno is set
 */

int _putchar(char c)
{
	static int a;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buffer, a);
		a = 0;
	}

	if (c != BUF_FLUSH)
	{
		buffer[a++] = c;
	}

	return (1);
}

