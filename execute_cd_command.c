/* execute_cd_command.c */
#include "execute_cd_command.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int execute_cd_command(char *dir) 
{
    if (dir != NULL) 
    {
        if (chdir(dir) != 0) 
        {
            perror("cd");
            return 1;  /* Return an error code*/
        }
        return 0;  /* Success*/
    } 
    else 
    {
        fprintf(stderr, "./hsh: cd: argument missing\n");
        return 1;  /* Return an error code*/
    }
}
