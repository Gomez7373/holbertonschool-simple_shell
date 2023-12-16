#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
extern char **environ;

/* Trims leading and trailing spaces from a string */
char *trim_whitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    return str;
}

/* Displays a prompt and reads a command */
int get_command(char *command, int interactive) {
    if (interactive) {
        printf("$ ");
    }
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
        return 0;
    }
    command[strcspn(command, "\n")] = 0;
    return 1;
}

/* Executes a command with arguments */
void execute_command(char *full_command) {
    char *argv[MAX_ARGS];
    char *token;
    int i = 0;
    pid_t pid;
    int status;

    token = strtok(full_command, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        if (argv[0][0] == '/' || strstr(argv[0], "./") == argv[0] || strstr(argv[0], "../") == argv[0]) {
            execv(argv[0], argv);  /* Direct execution for absolute or relative paths */
        } else {
            execvp(argv[0], argv);  /* Search in PATH for other cases */
        }
        fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
        exit(127);  /* Command not found */
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            exit(WEXITSTATUS(status));
        }
    }
}

/* Main function */
int main(void) {
    char command[MAX_COMMAND_LENGTH];
    int interactive = isatty(STDIN_FILENO);

    while (get_command(command, interactive)) {
        char *trimmed_command = trim_whitespace(command);
        if (strlen(trimmed_command) > 0) {
            execute_command(trimmed_command);
        }
    }

    if (interactive) {
        printf("\n");
    }
    return 0;
}
