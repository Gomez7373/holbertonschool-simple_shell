/* main.c*/
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#define EXIT_SUCCESS 0

int main(void)
{
    char *input;

    while (1)
    {
        printf("#cisfun$ ");
        input = read_inp();

        if (compare_str(input, "exit") == 0)
       	{
            free(input);
            exit(EXIT_SUCCESS);
        }

        _SHELL(input);

        free(input);
    }

    return (0);
}

