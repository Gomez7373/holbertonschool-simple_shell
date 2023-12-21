#ifndef MAIN_H
#define MAIN_H

/*
 * main.h
 * This is a header file with include guards to prevent double inclusion.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

/*char **environ;*/
extern char **environ;
extern void ctrlc_handler(int signum);

char *trim_whitespace(char *str);
int get_command(char *command, int interactive);
void execute_env(char **envp);
void execute_command(char *full_command, int *last_status);

#endif /* MAIN_H */

