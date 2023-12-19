#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

char **environ;

char *trim_whitespace(char *str)
{
char *end;
/* Trimming leading spaces */
while (isspace((unsigned char)*str))
str++;
if (*str == 0)
return (str);

/* Trimming trailing spaces */
end = str + strlen(str)
- 1;
while (end > str && isspace((unsigned char)*end))
end--;
*(end + 1) = 0;

return (str);
}

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

void execute_command(char *full_command, int *last_status)
{

    char *argv[MAX_ARGS];
    char *token;
    int i = 0, j;
    pid_t pid;
    int status;

    token = strtok(full_command, " ");
    while (token != NULL && i < MAX_ARGS - 1)
    {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    if (strcmp(argv[0], "env") == 0)
    {
        j = 0;
        while (environ[j] != NULL)
        {
            printf("%s\n", environ[j]);
            j++;
        }
        *last_status = 0;
        return;
    }
    if (strcmp(argv[0], "exit") == 0)
    {
        exit(*last_status);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (pid == 0)
    {
        dup2(STDOUT_FILENO, STDOUT_FILENO);
        dup2(STDERR_FILENO, STDERR_FILENO);
        execvp(argv[0], argv);

        dprintf(STDERR_FILENO, "./hsh: 1: %s: not found\n", argv[0]);
        exit(127);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            *last_status = WEXITSTATUS(status);
        }
    }
}

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    int interactive = isatty(STDIN_FILENO);
    int last_status = 0;

    while (get_command(command, interactive))
    {
        char *trimmed_command = trim_whitespace(command);
        if (strlen(trimmed_command) > 0)
        {
            execute_command(trimmed_command, &last_status);
        }
    }

    if (interactive)
    {
        printf("\n");
    }
    return (last_status);
}
