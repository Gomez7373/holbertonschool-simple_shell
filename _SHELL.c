/* _SHELL.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

void _SHELL(char *input) {
    pid_t pid;
    char **args;  /* Declare an array to store command and arguments */

    /* Tokenize the input into command and arguments */
    int arg_count = 0;
    char *token = strtok(input, " ");
    args = malloc(sizeof(char *));
    while (token != NULL) {
        args[arg_count] = token;
        arg_count++;
        args = realloc(args, (arg_count + 1) * sizeof(char *));
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;  /* Null-terminate the array */

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* Child process */
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        wait(NULL);
    }

    /* Free the allocated memory */
    free(args);
    printf("Executing: %s\n", input);
}

