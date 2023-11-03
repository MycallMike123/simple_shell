#include "shell.h"

int create_history(shell_t *cont);

/**
 * handle_history - gets the history file
 * @cont: pointer to the struct
 * Return: the string that conatins the hist file
 */

char *handle_history(shell_t *cont)
{
	char *direc;
	char *buffer;

	direc = getenv_command(cont, "HOME=");

	if (!direc)
	{
		return (NULL);
	}

	buffer = malloc(sizeof(char) * (_strlen(direc) + _strlen(HIST_FILE) + 2));

	if (!buffer)
	{
		return (NULL);
	}

	buffer[0] = 0;
	_strcpy(buffer, direc);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * handle_read_history - reads the history of a file
 * @cont: pointer to the struct
 * Return: historycount, 0 otherwise
 */

int handle_read_history(shell_t *cont)
{
	int a, b = 0, cnt = 0;
	char *buffer = NULL, *filename = handle_history(cont);
	ssize_t file_descriptor, len, filesize = 0;
	struct stat _stat;

	if (!filename)
		return (0);

	file_descriptor = open(filename, O_RDONLY);
	free(filename);

	if (file_descriptor == -1)
		return (0);

	if (!fstat(file_descriptor, &_stat))
		filesize = _stat.st_size;

	if (filesize < 2)
		return (0);

	buffer = malloc(sizeof(char) * (filesize + 1));

	if (!buffer)
		return (0);

	len = read(file_descriptor, buffer, filesize);
	buffer[filesize] = 0;
	if (len <= 0)
		return (free(buffer), 0);

	close(file_descriptor);
	for (a = 0; a < filesize; a++)
	{
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			handle_add_hist(cont, buffer + b, cnt++);
			b = a + 1;
		}
	}

	if (b != a)
		handle_add_hist(cont, buffer + b, cnt++);

	free(buffer);
	cont->history_count = cnt;

	while (cont->history_count-- >= HIST_MAX)
		del_node_idx(&(cont->history), 0);

	handle_numbering_hist(cont);
	return (cont->history_count);
}

/**
 * handle_numbering_hist - renumbers the history of a linked list
 * @cont: pointer to the struct
 * Return: the new histcount
 */

int handle_numbering_hist(shell_t *cont)
{
	int a;
	list_t *node = cont->history;

	a = 0;
	while (node)
	{
		node->num = a++;
		node = node->next;
	}

	return (cont->history_count = a);
}

/**
 * handle_add_list - Adds entry
 * @cont: pointer to the struct
 * @buffer: pointer to the buf
 * @line_cnt: the count of the history line count
 * Return: 0 Success
 */

int handle_add_list(shell_t *cont, char *buffer, int line_cnt)
{
	list_t *node = NULL;

	if (cont->history)
	{
		node = cont->history;
	}

	ending_node(&node, buffer, line_cnt);

	if (!cont->history)
	{
		cont->history = node;
	}

	return (0);
}

/**
 * create_history - craetes a file
 * @cont: pointer to the struct
 * Return: 1 success, -1 otherwise
 */

int create_history(shell_t *cont)
{
	char *file_name = handle_history(cont);
	ssize_t file_descriptor;
	list_t *node = NULL;

	if (!file_name)
	{
		return (-1);
	}

	file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (file_descriptor == -1)
	{
		return (-1);
	}

	for (node = cont->history; node; node = node->next)
	{
		input_fd_string(node->str, file_descriptor);
		input_file_descriptor('\n', file_descriptor);
	}

	input_fd_string(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}
