#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
extern char **environ;

/* Function to trim leading and trailing spaces */
char *trim_whitespace(char *str) {
    char *end;

    /* Trim leading space */
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  /* All spaces? */
        return str;

    /* Trim trailing space*/
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    /* Write new null terminator character*/
    *(end + 1) = 0;

    return str;
}

/* Function to display a prompt and read a command */
int get_command(char *command, int interactive) {
    if (interactive) {
        printf("$ ");
    }
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
        return 0;  /* EOF or error */
    }
    command[strcspn(command, "\n")] = 0;  /* Remove newline character */
    return 1;
}

/* Function to execute a command */
void execute_command(const char *command) {
    pid_t pid;
    int status;
    char *argv[2];

    argv[0] = (char *)command;  
    argv[1] = NULL;

    pid = fork();
    if (pid == -1) {
        perror("fork");
    } else if (pid == 0) {
        /* Child process */
        if (execve(command, argv, environ) == -1) {
            perror(command);
        }
        exit(EXIT_FAILURE);
    } else {
        /* Parent process */
        wait(&status);
    }
}

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
    return (0);
}
