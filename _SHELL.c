#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

char **environ;

char *trim_whitespace(char *str);
int get_command(char *command, int interactive);
int execute_command(char *full_command);
/**
 * main - The main function for the shell.
 *
 * Return: Always 0.
 */
int main(void)
{
char command[MAX_COMMAND_LENGTH];
int interactive = isatty(STDIN_FILENO);
int continue_shell = 1;

while (continue_shell && get_command(command, interactive))
{
char *trimmed_command = trim_whitespace(command);
if (strlen(trimmed_command) > 0)
{
continue_shell = execute_command(trimmed_command);
}
}

if (interactive)
{
printf("\n");
}
return (0);
}

/**
 * trim_whitespace - Removes leading and trailing whitespaces from a string.
 * @str: The input string.
 *
 * Return: A pointer to the trimmed string.
 */
char *trim_whitespace(char *str)
{
char *end;
while (isspace((unsigned char)*str))
{
str++;
}
if (*str == 0)
return (str);
end = str + strlen(str) - 1;
while (end > str && isspace((unsigned char)*end))
{
end--;
}
*(end + 1) = 0;
return (str);
}

/**
 * get_command - Gets a command from the user.
 * @command: Buffer to store the command.
 * @interactive: Flag indicating interactive mode.
 *
 * Return: 1 on success, 0 on failure.
 */
int get_command(char *command, int interactive)
{
if (interactive)
{
printf("$ ");
}
if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
{
return (0);
}
command[strcspn(command, "\n")] = 0;
return (1);
}

/**
 * execute_command - Executes a command in a separate process.
 * @full_command: The full command to be executed.
 *
 * Return: 1 to continue the shell, 0 to exit.
 */
int execute_command(char *full_command)
{
char *argv[MAX_ARGS];
char *token;
char *path_env; /* Declaration moved to the top */
int i = 0;
pid_t pid;
int status;

/* Initialize path_env */
path_env = getenv("PATH");

token = strtok(full_command, " ");
while (token != NULL && i < MAX_ARGS - 1)
{
argv[i++] = token;
token = strtok(NULL, " ");
}
argv[i] = NULL;

if ((path_env == NULL ||
strlen(path_env) == 0) && strchr(argv[0], '/') == NULL)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
exit(127);
}

/* Check for the env built-in */
if (strcmp(argv[0], "env") == 0)
{
char **env_var = environ;
while (*env_var != NULL)
{
printf("%s\n", *env_var);
env_var++;
}
return (1); /* Continue the shell */
}

/* Check for the exit built-in */
#ifdef EXIT_BUILTIN
if (strcmp(argv[0], "exit") == 0)
{
return (0); /* Signal to exit the shell */
}
#endif

pid = fork();
if (pid == -1)
{
perror("fork");
return (1);
}

if (pid == 0)
{
execvp(argv[0], argv);
fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
exit(127);
}
else
{
wait(&status);
}

return (1); /* Continue the shell */
}

