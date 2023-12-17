#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
extern char **environ;

/* Trim leading and trailing whitespaces from a string */
char *trim_whitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    return str;
}

/* Execute a command */
void execute_command(char *full_command) {
    char *argv[MAX_ARGS];
    char *token;
    char *path_env;
    int i = 0;
    pid_t pid;
    int status;

    path_env = getenv("PATH");

    /* Tokenize the command */
    token = strtok(full_command, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    /* Check for the 'exit' command */
    if (strcmp(argv[0], "exit") == 0) {
        exit(0);
    }

    /* Check if the command is found in the PATH */
    if ((path_env == NULL || strlen(path_env) == 0) && strchr(argv[0], '/') == NULL) {
        fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
        exit(127);
    }

    /* Fork a new process to execute the command */
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        /* In the child process */
        if ((path_env == NULL || strlen(path_env) == 0) && strchr(argv[0], '/') == NULL) {
            fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
            exit(127);
        }

        execvp(argv[0], argv);

        /* If execvp fails */
        fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
        exit(127);
    } else {
        /* In the parent process, wait for the child to finish */
        wait(&status);

        if (WIFEXITED(status)) {
            /* Print the exit status of the last command */
            printf("Exit status: %d\n", WEXITSTATUS(status));
        }
    }
}

/* Get a command from the user */
int get_command(char *command, int interactive) {
    if (interactive) {
        printf("$ ");
    }
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
        if (feof(stdin)) {
            /* Handle end of file (Ctrl+D) */
            return 0;  /* Return 0 to indicate end-of-file without exiting */
        } else {
            /* Error reading input */
            perror("fgets");
            exit(1);
        }
    }
    command[strcspn(command, "\n")] = 0;
    return 1;
}

/* Main function */
int main(void) {
    char command[MAX_COMMAND_LENGTH];
    int interactive = isatty(STDIN_FILENO);

    /* Main shell loop */
    while (1) {
        char *trimmed_command;

        if (!get_command(command, interactive)) {
            break;  /* Exit the loop when Ctrl+D is pressed */
        }

        trimmed_command = trim_whitespace(command);
        if (strlen(trimmed_command) > 0) {
            execute_command(trimmed_command);
        }
    }

    if (interactive) {
        printf("\n");
    }
    return 0;
}

