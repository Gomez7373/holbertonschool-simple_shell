/* main.h */
#ifndef MAIN_H
#define MAIN_H

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

extern char **environ;

char *trim_whitespace(char *str);
int get_command(char *command, int interactive);
void execute_command(char *full_command);

#endif /*MAIN_H */

