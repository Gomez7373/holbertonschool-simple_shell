/* read_inp.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

char *read_inp() {
    size_t len = 0;
    char *input = NULL;
    ssize_t read_bytes = getline(&input, &len, stdin);

    if (read_bytes == -1) {
        free(input);
        if (feof(stdin)) {
            printf("\n");
            exit(EXIT_SUCCESS);
        } else {
            perror("getline");
            exit(EXIT_FAILURE);
        }
    }

    input[strcspn(input, "\n")] = '\0';
    return (input);
}

