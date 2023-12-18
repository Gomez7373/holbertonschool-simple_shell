/* main.h */
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <ncurses.h>  /* Include curses header file */

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
extern char **environ;

/* Arrow key definitions */
#define ARROW_UP 1000
#define ARROW_DOWN 1001
#define ARROW_LEFT 1002
#define ARROW_RIGHT 1003

/* Function prototypes */
int read_arrow_key(void);
char *trim_whitespace(char *str);
int execute_cd_command(char *dir);
void execute_command(char *full_command);
int get_command(char *command, int interactive);

#endif /* MAIN_H */

