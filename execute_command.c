/* main.c */
#include "main.h"
#include "execute_command.h"
void execute_command(char *full_command) 
{
    char *argv[MAX_ARGS];
    char *token;
    char *path_env; /* Declaration moved to the top */
    int i = 0;
    pid_t pid;
    int status;

    /* Initialize path_env */
    path_env = getenv("PATH");

    token = strtok(full_command, " ");
    while (token != NULL && i < MAX_ARGS - 1) 
    {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    if (strcmp(argv[0], "cd") == 0) 
    {
        /* Handle "cd" separately */
        execute_cd_command(argv[1]);
    } 
    else 
    {
        /* Handle other commands */
        if ((path_env == NULL || strlen(path_env) == 0) && strchr(argv[0], '/') == NULL) 
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
            /* exit(127); */ /* Comment out this line for testing */
        }

        pid = fork();
        if (pid == -1) 
        {
            perror("fork");
            return;
        }

        if (pid == 0) 
        {
            execvp(argv[0], argv);
            fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
            /* exit(127); */ /* Comment out this line for testing */
        } 
        else 
        {
            waitpid(pid, &status, 0); /* Wait for the child process to complete */
        }
    }

    printf("\n"); /* Add this line to print a newline after command execution */
    return;
}

