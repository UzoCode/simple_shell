#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>

#ifdef __GNUC__
#define UNUSED __attribute__((__unused__))
#endif

#define BUFFER_SIZE 128
#define PATH_MAX 4096

extern char **environ;

/**
 * struct builtin_t - builtin function
 * @name: name of builtin function
 * @func: pointer to builtin function
 */
typedef struct builtin_t
{
	char *name;
	int (*func)(char **argv);

} builtin_t;

int prompts(size_t signum);
void exit_with_errors(int code, char *shell, const char *filename);
int execute_commands_from_files(char **argv);
char *handle_paths(char *cmd);
int run_commands(char **argv);
int execute_commands(char **argv);

/*-----------builtin function------------------*/
int (*handles_builtin_func(char *s))(char **argv);
typedef int (*get_builtin)(char **argv);
int modifyenv(char **argv);
int exit_simple_shells(char **argv);
int printenv(char **argv UNUSED);
int changes_working_dir(char **argv);
/*--------------------------------------------*/

void trims(char **str);
int gets_argv(char ***argv);
void frees_argv(char **argv);
int resizes_argv(char ***argv, size_t *max_argc);
char *_getenvs(const char *name);
char **creates_env_table(char **envp);

ssize_t _getlines(char **lineptr, size_t *n, FILE *stream);
ssize_t readlines(char **lineptr, size_t *n, int fd);
int resize_getline_bufs(char **lineptr, size_t *n, size_t new_size);
int creates_new_env(char *name, char *value);
int _setenvs(char *name, char *value, int overwrite);
int _unsetenvs(char *name);

size_t _strlen(const char *str);
char *_strchr(const char *strs, int characters);
char *_strtok(char *str, const char *delim);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
char *_strcats(char *dest, char *str1, char *str2, char delim);
int _strncmps(const char *str1, const char *str2, size_t n);
int _strcmps(const char *str1, const char *str2);

char *_memsets(char *s, char b, unsigned int n);
char *_memcpys(char *dest, char *src, unsigned int n);
void *_reallocs(void *ptr, size_t size);

void cmd_not_found(char *cmd);

#endif /*SHELL_H*/
