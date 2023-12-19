/* execute_cd_command.c */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void execute_cd_command(char *command)
{
    if (command != NULL)
    {
        if (chdir(command) != 0)
        {
            perror("cd");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("No directory specified for cd command.\n");
        return;  /* Return without exiting the program*/
    }
}

