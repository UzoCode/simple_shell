#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>

#define MAX_COMMAND_LENGTH 1024
int process(void);
int processtwo(void);
int main(int argc, char *argv[]);
char *_getenv(const char *name);
int path_direct(void);
PATH *buildpath_list(void);
int main(int ac __attribute__((unused)), char **av);
void freestr_array(char **str_ptr);
char **split_strings(char *str, const char *delim);
void prompts();
int main(int ac, char **av);
int _unsetenvs(const char *names);
int _setenvs(const char *names, const char *values, int overwrites);
int _setenv_news(const char *names, const char *values);

#endif
