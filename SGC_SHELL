#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
extern char **environ;

/**
 * trim_whitespace - Removes leading and trailing whitespaces from a string.
 * @str: The input string.
 * Return: A pointer to the trimmed string.
 */
char *trim_whitespace(char *str)
{
    char *end;
    while (isspace((unsigned char)*str))
        str++;
    if (*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    *(end + 1) = 0;
    return str;
}

/**
 * get_command - Reads a command from the user.
 * @command: Buffer to store the command.
 * @interactive: Flag indicating if the shell is in interactive mode.
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
        return 0;
    }
    command[strcspn(command, "\n")] = 0;
    return 1;
}

/**
 * command_exists - Checks if a command exists in the PATH.
 * @command: The command to check.
 * Return: 1 if the command exists, 0 otherwise.
 */
int command_exists(const char *command)
{
    return access(command, X_OK) == 0;
}

/**
 * execute_command - Executes a command.
 * @full_command: The full command to execute.
 */
void execute_command(char *full_command)
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

    if ((path_env == NULL || strlen(path_env) == 0) && strchr(argv[0], '/') == NULL)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
        exit(127);
    }

    if (!command_exists(argv[0]))
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
        exit(127);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
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
}

/**
 * main - The main function of the simple shell.
 * Return: Always 0.
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    int interactive = isatty(STDIN_FILENO);

    while (get_command(command, interactive))
    {
        char *trimmed_command = trim_whitespace(command);
        if (strlen(trimmed_command) > 0)
        {
            execute_command(trimmed_command);
        }
    }

    if (interactive)
    {
        printf("\n");
    }
    return 0;
}

