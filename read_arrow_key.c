/* read_arrow_key.c */
#include <ncurses.h>
#include <stdio.h>

/* Declare constants for arrow keys */
#define ARROW_UP    1000
#define ARROW_DOWN  1001
#define ARROW_LEFT  1002
#define ARROW_RIGHT 1003

int read_arrow_key(char *command)
{
    int ch = getch();  /* Use getch to read a character */

    switch (ch)
    {
    case KEY_UP:
        return ARROW_UP;
    case KEY_DOWN:
        return ARROW_DOWN;
    case KEY_LEFT:
        return ARROW_LEFT;
    case KEY_RIGHT:
        return ARROW_RIGHT;
    default:
        printf("Reading arrow key for command: %s\n", command);
        return ch;  /* Return other characters as-is */
    }
}

