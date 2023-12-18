/* arrow_key_handler.c */
#include "main.h"
#include <ncurses.h>
#include "arrow_key_handler.h"
int read_arrow_key() 
{
    int ch;

    initscr();
    raw();
    keypad(stdscr, TRUE);

    ch = getch();

    endwin();
    return ch;
}

