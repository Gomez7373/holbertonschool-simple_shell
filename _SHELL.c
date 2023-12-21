#include "main.h"

/**
* trim_whitespace - Trim leading and trailing whitespaces from a string
* @str: Input string
*
* Return: Trimmed string
*/
char *trim_whitespace(char *str)
{
char *end;

/* Trim leading spaces */
while (isspace((unsigned char)*str))
str++;

if (*str == 0)
return (str);

/* Trim trailing spaces */
end = str + strlen(str) - 1;
while (end > str && isspace((unsigned char)*end))
end--;

*(end + 1) = 0;

return (str);
}

/**
* get_command - Get user input for the command
* @command: Buffer to store user input
* @interactive: Flag indicating interactive mode
*
* Return: 1 if successful, 0 if there's an error
*/
int get_command(char *command, int interactive)
{
if (interactive)
printf("$ ");

if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
return (0);

command[strcspn(command, "\n")] = 0;

return (1);
}

/**
* execute_command - Execute a shell command
* @full_command: Full command string
* @last_status: Pointer to last command's exit status
*/
void execute_command(char *full_command, int *last_status)
{
char *argv[MAX_ARGS], *t;
int i = 0, s, j;
pid_t p = -1;
for (t = strtok(full_command, " ");
t && i < MAX_ARGS - 1; t = strtok(NULL, " "))
argv[i++] = t;
argv[i] = NULL;
if (strcmp(argv[0], "env") == 0)
{
if (environ != NULL)
for (j = 0; environ[j] != NULL; ++j)
printf("%s\n", environ[j]);
}
else if (strcmp(argv[0], "exit") == 0)
{
exit(*last_status);
}
else
{
if (getenv("PATH") == NULL && strcmp(argv[0], "ls") == 0)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
*last_status = 127;
return;
}
p = fork();
if (p == -1)
perror("fork");
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
/**
* main - Shell entry point
*
* Return: Last command exit status
*/
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
printf("\n");

return (last_status);
}
/**
 * Main - Shell entry Point
 *
 * Return: Last command exit status
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	int interactive = isatty(STDIN_FILENO);
	int last_status = 0;
if (signal(SIGINT, ctrlc_handler) == SIG_ERR)
{
perror("signal");
return EXIT_FAILURE;
}
while (get_command(command, interactive))
{
char *trimmed_command = trim_whitespace(command);
if (strlen(trimmed_command) > 0)
{
execute_command(trimmed_command, &last_status);
}
}
if (interactive)
pritnf("\n");
return (last_status);
}
