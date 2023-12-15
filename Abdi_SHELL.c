#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
extern char **environ;

char *trim_whitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    return str;
}

int get_command(char *command, int interactive) {
    if (interactive) {
        printf("$ ");
    }
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
        return 0;
    }
    command[strcspn(command, "\n")] = 0;
    return 1;
}

/* Function to search for a command in PATH */
char *search_in_path(char *cmd) {
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *token = strtok(path_copy, ":");
    char *cmd_path = malloc(MAX_COMMAND_LENGTH);
    
    while (token != NULL) {
        sprintf(cmd_path, "%s/%s", token, cmd);
        if (access(cmd_path, X_OK) == 0) {
            free(path_copy);
            return cmd_path;
        }
        token = strtok(NULL, ":");
    }

    free(path_copy);
    free(cmd_path);
    return NULL;
}

void execute_command(char *full_command) {
    char *argv[MAX_ARGS];
    char *token;
    int i = 0;
    pid_t pid;
    int status;

    token = strtok(full_command, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    if (strchr(argv[0], '/') == NULL) {
        char *path_cmd = search_in_path(argv[0]);
        if (path_cmd == NULL) {
            fprintf(stderr, "%s: Command not found\n", argv[0]);
            return;
        }
        free(path_cmd);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        if (execvp(argv[0], argv) == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        wait(&status);
    }
}

int main(void) {
    char command[MAX_COMMAND_LENGTH];
    int interactive = isatty(STDIN_FILENO);

    while (get_command(command, interactive)) {
        char *trimmed_command = trim_whitespace(command);
        if (strlen(trimmed_command) > 0) {
            execute_command(trimmed_command);
        }
    }

    if (interactive) {
        printf("\n");
    }
    return 0;
}
