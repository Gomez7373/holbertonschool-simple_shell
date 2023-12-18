/* read_arrow_key.c */
#include "main.h"
#include "read_arrow_key.h"
int read_arrow_key(void) {
    int ch = getch();  /* Use getch to read a character */
    switch (ch) {
        case KEY_UP:
            return ARROW_UP;
        case KEY_DOWN:
            return ARROW_DOWN;
        case KEY_LEFT:
            return ARROW_LEFT;
        case KEY_RIGHT:
            return ARROW_RIGHT;
        default:
            return ch;  /* Return the ASCII value for other keys */
    }
}

