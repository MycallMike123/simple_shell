#include "shell.h"

/**
 * print_decimal - prints a decimal
 * @input: the input
 * @file_descriptor: the fd to write
 * Return: No of chars printed
 */

int print_decimal(int input, int file_descriptor)
{
	int cnt = 0, a;
	int (*__putchar)(char) = _putchar;
	unsigned int _abs_, num_curr;

	if (file_descriptor == STDERR_FILENO)
	{
		__putchar = print_char;
	}

	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		cnt++;
	}

	else
	{
		_abs_ = input;
	}

	num_curr = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + num_curr / a);
			cnt++;
		}

		num_curr %= a;
	}
	__putchar('0' + num_curr);
	cnt++;

	return (cnt);
}

/**
 * convert_num - converts function num
 * @num: the number to convert
 * @b: the base of the number to convert
 * @fl: The flags arguments
 * Return: The string of the num converted
 */

char *convert_num(long int num, int b, int fl)
{
	static char *arr;
	static char buf[50];
	char sign = 0;
	char *p;
	unsigned long n = num;

	if (!(fl & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	arr = fl & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";

	p = &buf[49];
	*p =  '\0';

	do {
		*--p = arr[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
	{
		*--p = sign;
	}

	return (p);
}

/**
 * print_err - prints an error message
 * @cont: pointer to the struct
 * @err_type: - pointer to specified error type
 */

void print_err(shell_t *cont, char *err_type)
{
	input_str(cont->file_name);
	input_str(": ");
	print_decimal(cont->lc, STDERR_FILENO);
	input_str(": ");
	input_str(cont->argv[0]);
	input_str(": ");
	input_str(err_type);
}

/**
 * handle_comments - replaces first instance of '#' with '\0'
 * @buffer: pointer to the string to modify
 */

void handle_comments(char *buffer)
{
	int a;

	for (a = 0; buffer[a] != '\0'; a++)
	{
		if (buffer[a] == '#' && (!a || buffer[a - 1] == ' '))
		{
			buffer[a] = '\0';
			break;
		}
	}
}

/**
 * handle_sigint - blocks ctrl-C
 * @sig_n: the signal number
 */

void handle_sigint(__attribute__((unused))int sig_n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
