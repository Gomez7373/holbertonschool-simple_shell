#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
extern char **environ;

/* Function to trim leading and trailing spaces */
char *trim_whitespace(char *str) {
    char *end;

    /* Trim leading space */
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  /* All spaces? */
        return str;

    /* Trim trailing space */
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    /* Write new null terminator character */
    *(end + 1) = 0;

    return str;
}

/* Function to display a prompt and read a command */
int get_command(char *command, int interactive) {
    if (interactive) {
        printf("#cisfun$ ");
    }
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
        return 0;  /* EOF or error */
    }
    command[strcspn(command, "\n")] = 0;  /* Remove newline character */
    return 1;
}

/* Function to execute a command with arguments */
void execute_command(char *full_command) {
    char *argv[MAX_ARGS];
    char *token;
    int i = 0;
    pid_t pid;

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
        execvp(argv[0], argv);
        fprintf(stderr, "./hsh: %s: not found\n", argv[0]);
        exit(127);
    } else {
        /* Parent process */
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            exit(WEXITSTATUS(status));
        }
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
