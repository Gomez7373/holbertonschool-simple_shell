/* get_command.c */
#include <stdio.h>
#include <string.h>
#ifndef GET_COMMAND_H
#define GET_COMMAND_H

#define MAX_COMMAND_LENGTH 1024

int get_command(char *command, int interactive)
{
    if (interactive)
    {
        printf("$ ");  /* Use printf for interactive mode */
        fflush(stdout);  /* Flush stdout to ensure the prompt is displayed */
    }

    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
    {
        return 0;
    }

    command[strcspn(command, "\n")] = '\0';  /* Remove newline character */
    return 1;
}
#endif /* GET_COMMAND_H */
