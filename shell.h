#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

#define HIST_MAX 4096
#define HIST_FILE ".simple_shell_history"
#define CONVERT_UNSIGNED 2
#define CONVERT_LOWERCASE 1
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define CMD_CHAIN 3
#define CMD_OR 1
#define CMD_AND 2
#define CMD_NORM 0
#define USE_STRTOK 0
#define USE_GETLINE 0

extern char **environ;

int _strlen(char *s);
char *commence(const char *hay, const char *needle);
char *_memset(char *s, char b, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void ffree(char **str);

/**
 * struct pseudo_arg - contains arguments to pass to fns
 * @argv:an array of strings
 * @argc: the argument count
 * @number_error: the error code for exit
 * @file_name: the filename
 * @environ: custom modified copy of environ
 * @alias: the alias node
 * @process: the return status of the command executed
 * @command_buffer_type: The buffer type
 * @history_count: the history line number count
 * @read_file_descriptor: the fd to read line input
 * @command_buffer: address of pointer to command_buffer
 * @environ_c: shows if environ was changed
 * @history: the history node
 * @env: linked list copy of environ
 * @lcf: linecount flag
 * @lc: the error count
 * @path: a string path
 * @arg: a string generated from getline
 */

typedef struct pseudo_arg
{
	char **argv;
	int argc;
	int number_error;
	char *file_name;
	char **environ;
	list_t *alias;
	int process;
	int command_buffer_type;
	int history_count;
	int read_file_descriptor;
	char **command_buffer;
	int environ_c;
	list_t *history;
	list_t *env;
	int lcf;
	unsigned int lc;
	char *path;
	char *arg;
} shell_t;
i
/**
 * struct lss - singly linked list
 * @num: the number
 * @str: the string
 * @next: points to the next node
 */

typedef struct lss
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct builtin - contains a builtin str and related function
 * @type: the builtin command_flag
 * @fn: the function
 */

typedef struct builtin
{
	char *type;
	int (*fn)(shell_t *);
} bi_t;

int handle_command(shell_t *cont, char *path);
char *handle_find_path(shell_t *cont, char *_path, char *cmd);
char *duplicate_char(char *_path, int st_idx, int sp_idx);
int _free(void **p);
int string_substitute(char **old, char *_new);
int alias_substitute(shell_t *cont);
int chain_check(shell_t *cont, char *buf, size_t *ptr);
void handle_chain(shell_t *cont, char *buf, size_t *ptr, size_t a, size_t len);
int var_substitute(shell_t *cont);

int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
void _puts(char *str);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
int _delimeter(char s, char *del);
int _isalpha(int s);
int str_to_int(char *s);

list_t *handle_node(list_t **_start, const char *str, int num);
list_t *ending_node(list_t **_start, const char *str, int num);
ssize_t getnode_idx(list_t *_start, list_t *node);
list_t *start_node(list_t *node, char *pref, char c);
int del_node_idx(list_t **_start, unsigned int idx);
size_t string_list(const list_t *p);
void handle_freelist(list_t **_start);
size_t list_print(const list_t *p);
size_t handle_list_length(const list_t *p);
char **lts(list_t *_start);

int hsh(shell_t *cont, char **argv);
void command_fork(shell_t *cont);
void find_command(shell_t *cont);
int find_b(shell_t *cont);

#endif
