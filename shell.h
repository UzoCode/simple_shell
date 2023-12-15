#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


int process(void);
int processtwo(void);
int main(int argc, char *argv[]);
char *_getenv(const char *name);
int path_direct(void);
PATH *buildpath_list(void);

#endif
