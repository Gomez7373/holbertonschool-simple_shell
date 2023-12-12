#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_ARGS 64
extern char **environ;

/* Function to execute a command with arguments */
void execute_command(char *full_command) {
    pid_t pid;
    int status;
    char *argv[MAX_ARGS];
    char *token;
    int i = 0;

    /* Split the command into words */
    token = strtok(full_command, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    /* Execute the command */
    pid = fork();
    if (pid == -1) {
        perror("fork");
    } else if (pid == 0) {
        /* Child process */
        if (execvp(argv[0], argv) == -1) {
            perror(argv[0]);
        }
        exit(EXIT_FAILURE);
    } else {
        /* Parent process */
        waitpid(pid, &status, 0);
    }
}

int main(void) {
    char *command;
    int interactive = isatty(STDIN_FILENO);

    while ((command = readline("#cisfun$ ")) != NULL) {
        if (strlen(command) > 0) {
            add_history(command);
            execute_command(command);
        }
        free(command);
    }

    if (interactive) {
        printf("\n");
    }
    return (0);
}

