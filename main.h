#ifndef MAIN_H
#define MAIN_H

/*
 * main.h
 * This is a header file with include guards to prevent double inclusion.
 */

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

extern char **environ;

char *trim_whitespace(char *str);
int get_command(char *command, int interactive);
void execute_command(char *full_command, int *last status);
void execute_env(char **envp)
{
#endif /* MAIN_H */

