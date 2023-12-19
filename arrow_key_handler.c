/* arrow_key_handler.c */

#include <ncurses.h>
#include <stdio.h>
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

