#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

void execmd(char **argv);
char *get_location(char *command);
