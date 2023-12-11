#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>  /* Include for wait */

#define MAX_COMMAND_LENGTH 1024
extern char **environ;

/* Function to display a prompt and read a command */
int get_command(char *command) {
    printf("$ ");
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
    char *argv[2];  /* Declare the array */

    pid = fork();
    if (pid == -1) {
        perror("fork");
    } else if (pid == 0) {
        /* Child process */
        argv[0] = (char *)command;  /* Assign the value to the array */
        argv[1] = NULL;
        if (execve(command, argv, environ) == -1) {
            perror(command);
        }
        exit(EXIT_FAILURE);  /* execve only returns on error */
    } else {
        /* Parent process */
        wait(&status);  /* Wait for the child process */
    }
}

int main(void) {
    char command[MAX_COMMAND_LENGTH];

    while (get_command(command)) {
        if (strlen(command) > 0) {
            execute_command(command);
        }
    }

    printf("\n");
    return 0;
}
