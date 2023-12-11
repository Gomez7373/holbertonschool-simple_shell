/* _SHELL.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

void _SHELL(char *input) {
    pid_t pid;
    char *argv[2];  /* Declare the array */

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* Child process */
        argv[0] = input;
        argv[1] = NULL;  /* Initialize the array */
        if (execve(input, argv, (char *const *)NULL) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        wait(NULL);
    }
    printf("Executing: %s\n", input);
}

