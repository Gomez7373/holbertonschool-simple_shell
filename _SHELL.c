#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#define MAX_COMMAND_LENGTH 1024/*NEW*/
#define MAX_ARGS 64
extern char **environ;

/* Function to execute a command with arguments */
void execute_command(char *full_command) {
    char *argv[MAX_ARGS];
    char *token;
    int i = 0;
    pid_t pid;  /* Declaration moved to the top of the block */

    /* Split the command into words */
    token = strtok(full_command, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    /* Fork process to execute command */
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        /* Child process */
        if (execvp(argv[0], argv) == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        int status;
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
