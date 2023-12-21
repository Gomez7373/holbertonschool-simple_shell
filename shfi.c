#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include "main.h"

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64


extern char **environ;

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

        if (interactive)
        {
            printf(" ");
            fflush(stdout);
        }
    }

    if (interactive)
        printf("\n");

    return last_status;
}

/*-------------------------------------------------*/
int get_command(char *command, int interactive)
{
if (interactive)
{
printf("$ ");
fflush(stdout);
}

if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
return (0);

command[strcspn(command, "\n")] = 0;

return (1);
}
/*---------------------------------------------------*/
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

return (str);
}
/*------------------------------------------------------*/
void execute_env(char **envp)
{
    char **env_ptr = envp;
    size_t length = 0;

    if (env_ptr == NULL)
    {
        fprintf(stderr, "Error: Environment is not properly set.\n");
        exit(1);
    }

    printf("(stdout)[");
    while (*env_ptr != NULL)
    {
        printf("%s\n", *env_ptr);
        length += strlen(*env_ptr) +1;
        env_ptr++;
    }
    printf("](Length: %lu)\n", length);
    printf("(stderr)[](Length: 0)\n");
    printf("(status)[0]\n\n");

    printf("Environment:\n");
    env_ptr = envp;
    while (*env_ptr != NULL)
    {
        printf("%s\n", *env_ptr);
        env_ptr++;
    }
    printf("(Length: %lu)\n", (unsigned long)length);
    printf("(stderr)[](Length: 0)\n");
    printf("(status)[0]\n\n");
}

/*-------------------------------------------------------*/
void execute_command(char *full_command, int *last_status)
{
char *argv[MAX_ARGS], *t;
int i = 0, s;
pid_t p;

for (t = strtok(full_command, " ");
t && i < MAX_ARGS - 1;
t = strtok(NULL, " "))
argv[i++] = t;

argv[i] = NULL;

if (strcmp(argv[0], "env") == 0)
{
execute_env(environ);
}
else if (strcmp(argv[0], "exit") == 0)
{
exit(*last_status);
}
else
{
p = fork();
if (p == -1)
{
perror("fork");
exit(1);
}
else if (p == 0)
{
execvp(argv[0], argv);
fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
exit(127);
}
else
{
waitpid(p, &s, 0);
*last_status = WIFEXITED(s) ? WEXITSTATUS(s) : *last_status;
}
}
}
