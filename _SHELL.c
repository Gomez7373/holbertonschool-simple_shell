#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

char **environ;
/*------------------------------------------------------------*/
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
/*------------------------------------------------------------*/

/*
* execute_command - Execute a shell command
* @full_command: Full command string
* @last_status: Pointer to last command's exit status
*/
void execute_command(char *full_command, int *last_status)
{
char *argv[64], *t;
int i = 0, j, s;
pid_t p;

for (t = strtok(full_command, " "); t && i < 63; t = strtok(NULL, " "))
argv[i++] = t;

argv[i] = NULL;

if (strcmp(argv[0], "env") == 0)
for (j = 0; environ[j] != NULL;
printf("%s\n", environ[j++]));
else if (strcmp(argv[0], "exit") == 0)
exit(*last_status);
else if ((p = fork()) == -1)
perror("fork");
else if (p == 0)
{
dup2(STDIN_FILENO, STDIN_FILENO);
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
/*------------------------------------------------------------*/
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
