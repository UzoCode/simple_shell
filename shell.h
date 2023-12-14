#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int fork(void);
int main(void);
int assist(int argc, char *argv[]);
#endif
