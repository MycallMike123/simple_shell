#include "shell.h"

/**
 * getline_command - gets the next line
 * @cont: pointer to the struct
 * @p: pointer to the buf
 * @len: size of the buf
 * Return: the string, -1 otherwise
 */

int getline_command(shell_t *cont, char **p, size_t *len)
{
	static size_t a, length;
	static char buf[READ_BUF_SIZE];
	size_t i;
	ssize_t x = 0, z = 0;
	char *ptr = NULL, *n_ptr = NULL, *c;

	ptr = *p;
	if (ptr && len)
		z = *len;

	if (a == length)
		a = length = 0;

	x = buffer_read(cont, buf, &length);

	if (x == -1 || (x == 0 && length == 0))
		return (-1);

	c = _strchr(buf + a, '\n');
	i = c ? 1 + (unsigned int)(c - buf) : length;
	n_ptr = _realloc(ptr, z, z ? z + i : i + 1);

	if (!n_ptr)
		return (ptr ? free(ptr), -1 : -1);

	if (z)
		_strncat(n_ptr, buf + a, i - a);

	else
		_strncpy(n_ptr, buf + a, i - a + 1);

	z += i - a;
	a = i;
	ptr = n_ptr;

	if (len)
		*len = z;
	*p = ptr;

	return (z);
}

/**
 * _strchr - Locates a char in a string
 * @s: Pointer to the string to search
 * @c: The character to locate
 * Return: A pointer to char c or NULL if not found
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * buffer_input - Program that buffers chain commands
 * @cont: pointer to the struct
 * @buffer: pointer to the buffer
 * @length: pointer to the length of the buffer
 * Return: read bytes
 */

ssize_t buffer_input(shell_t *cont, char **buffer, size_t *length)
{
	ssize_t _read = 0;
	size_t len = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sigint);
#if USE_GETLINE
		_read = getline(buffer, &len, stdin);
#else
		_read = getline_command(cont, buffer, &len);
#endif
		if (_read > 0)
		{
			if ((*buffer)[_read - 1] == '\n')
			{
				(*buffer)[_read - 1] = '\0';
				_read--;
			}
			cont->lcf = 1;
			handle_comments(*buffer);
			handle_add_hist(cont, *buffer, cont->history_count++);

			if (_strchr(*buffer, ';'))
			{
				*length = _read;
				cont->command_buffer = buffer;
			}
		}
	}
	return (_read);
}

/**
 * buffer_read - reads a buf
 * @cont: pointer to ther struct
 * @buffer: pointer to the buffer
 * @length: pointer to the length of the buffer
 * Return: The read buf
 */

ssize_t buffer_read(shell_t *cont, char *buffer, size_t *length)
{
	ssize_t _read = 0;

	if (*length)
	{
		return (0);
	}

	_read = read(cont->read_file_descriptor, buffer, READ_BUF_SIZE);

	if (_read >= 0)
	{
		*length = _read;
	}

	return (_read);
}

/**
 * get_line - gets a line minus the newline
 * @cont: pointer to ther struct
 * Return: The read bytes
 */

ssize_t get_line(shell_t *cont)
{
	static size_t length, a, b;
	static char *buffer;
	ssize_t _read = 0;
	char **buf = &(cont->arg), *ptr;

	_putchar(BUF_FLUSH);

	_read = buffer_input(cont, &buffer, &length);

	if (_read == -1)
		return (-1);

	if (length)
	{
		b = a;

		ptr = buffer + a;

		handle_chain(cont, buffer, &b, a, length);
		while (b < length)
		{
			if (chain_check(cont, buffer, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= length)
		{
			a = length = 0;
			cont->command_buffer_type = CMD_NORM;
		}

		*buf = ptr;
		return (_strlen(ptr));
	}
	*buf = buffer;
	return (_read);
}

