#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64
#define MAX_PROCESSES 256

struct Process {
    char command[256];
};

void free_args(char **args) {
    int i;
    for (i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}

void execute_env(void) {
    extern char **environ;
    char **env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
}

void tokenize_input(char *input, char **args, int *arg_count) {
    char *token = strtok(input, " ");
    while (token != NULL) {
        args[*arg_count] = malloc(strlen(token) + 1);
        strcpy(args[*arg_count], token);
        (*arg_count)++;
        token = strtok(NULL, " ");
    }
}

void execute_builtin(char **args) {
    printf("Executing built-in command: %s\n", args[0]);
}

void execute_command(char **args, struct Process *processes, int *num_processes) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        char command[256];
        sprintf(command, "%s", args[0]);
        strcpy(processes[*num_processes].command, command);
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        (*num_processes)++;
    }
}

int main(void) {
    struct Process processes[MAX_PROCESSES];
    char *input = NULL;
    char *args[MAX_ARGS];
    int num_processes = 0;
    int arg_count;

    while (1) {
        printf("simple_shell$ ");
        fgets(input, MAX_ARGS, stdin);

        if (input[0] == '\n') {
            continue;
        }

        input[strcspn(input, "\n")] = '\0';

        arg_count = 0;

        tokenize_input(input, args, &arg_count);

        if (arg_count > 0) {
            if (strcmp(args[0], "cd") == 0) {
                /* Handle cd command*/
            } else if (strcmp(args[0], "exit") == 0) {
                free_args(args);
                free(input);
                exit(EXIT_SUCCESS);
            } else if (strcmp(args[0], "env") == 0) {
                execute_env();
            } else {
                execute_command(args, processes, &num_processes);
            }
        }

        free_args(args);
    }

    free(input);

    return 0;
}

