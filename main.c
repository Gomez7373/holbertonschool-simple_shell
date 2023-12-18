#include <stdio.h>

/* Define function pointer type */
typedef void (*CommandFunctionVoid)(char *);
typedef int (*CommandFunctionInt)(char *);
typedef int (*CommandFunctionIntArg)(char *, int);
typedef char *(*CommandFunctionCharPtr)(char *);

/* Function prototypes */
void execute_cd_command(char *command);
int arrow_key_handler(char *command);
int get_command(char *command);
char *trim_whitespace(char *command);

/* Define a struct for function pointers */
struct CommandFunctions
{
    CommandFunctionVoid voidFunctions;
    CommandFunctionInt intFunctions;
    CommandFunctionIntArg intArgFunctions;
    CommandFunctionCharPtr charPtrFunctions;
};

/* Array of function pointers */
struct CommandFunctions commandFunctions[] = {
    {
        execute_cd_command,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        arrow_key_handler,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        (CommandFunctionIntArg)get_command,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        trim_whitespace
    }
    /* Add more functions as needed */
};

int main(void)
{
    char *trimmed_command = "ls -l";

    /* Call functions in a loop */
    for (size_t i = 0; i < sizeof(commandFunctions) / sizeof(commandFunctions[0]); ++i)
    {
        if (commandFunctions[i].voidFunctions != NULL)
        {
            commandFunctions[i].voidFunctions(trimmed_command);
        }
        else if (commandFunctions[i].intFunctions != NULL)
        {
            commandFunctions[i].intFunctions(trimmed_command);
        }
        else if (commandFunctions[i].intArgFunctions != NULL)
        {
            int some_value = 42;
            commandFunctions[i].intArgFunctions(trimmed_command, some_value);
        }
        else if (commandFunctions[i].charPtrFunctions != NULL)
        {
            commandFunctions[i].charPtrFunctions(trimmed_command);
        }
    }

    return 0;
}

/* Implementations of the functions */
void execute_cd_command(char *command)
{
    printf("Executing cd command: %s\n", command);
}

int arrow_key_handler(char *command)
{
    printf("Handling arrow keys for command: %s\n", command);
    return 0;
}

int get_command(char *command)
{
    printf("Getting command: %s\n", command);
    return 0;
}

char *trim_whitespace(char *command)
{
    printf("Trimming whitespace from command: %s\n", command);
    return command;
}

