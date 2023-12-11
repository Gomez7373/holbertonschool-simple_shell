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
    
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* Child process */
        char *token = strtok(input, " \t\n");
        char *argv[64];
        int i = 0;

        while (token != NULL) {
            argv[i++] = token;
            token = strtok(NULL, " \t\n");
        }

        argv[i] = NULL;

        if (execvp(argv[0], argv) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        wait(NULL);
    }

    printf("Executing: %s\n", input);
}

