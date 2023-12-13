#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>


/*constants*/
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 *struct map - a struct that maps a command name to a function 
 *
 *@command_name: name of the command
 *@func: the function that executes the command
 */

typedef struct map
{
	char *command_names;
	void (*func)(char **command);
} function_map;

extern char **environs;
extern char *lines;
extern char **command;
extern char *shell_names;
extern int statue;

/*assist*/
void prints(char *, int);
char **tokenize(char *, char *);
void removes_newlines(char *);
int _strlens(char *);
void _strcpys(char *, char *);

/*assist2*/
int _strcmps(char *, char *);
char *_strcats(char *, char *);
int _strspns(char *, char *);
int _strcspns(char *, char *);
char *_strchrs(char *, char);

/*assist2*/
char *_strtok_s(char *, char *, char **);
int _atoi_i(char *);
void *_reallocs(void *ptrs, unsigned int old_sizes, unsigned int new_sizes);
void ctrl_c_handle(int);
void removes_comments(char *);

/*tools*/
int parse_commands(char *);
void execute_commands(char **, int);
char *checks_path(char *);
void (*get_funcs(char *))(char **);
char *_getenvs(char *);

/*built_in*/
void env(char **);
void quit(char **);

/*main*/
extern void non_interacting(void);
extern void initialize(char **recent_command, int types_commands);

#endif /*SHELL_H*/
