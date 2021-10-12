/* triangle.c */

#include <curses.h>
#include <stdlib.h>
#include <time.h>

#include <gui.h>

#define ITERMAX 10000

int main(void)
{
    long iter;
    int yi, xi;
    int y[2], x[2];
    int index;
    int maxlines, maxcols;
    srand(time(NULL));

    /* initialize curses */

    initscr();
    cbreak();
    noecho();

    clear();

    /* initialize triangle */

    maxlines = LINES - 1;
    maxcols = COLS - 1;

    y[0] = 0;
    x[0] = 0;

    y[1] = maxlines;
    x[1] = maxcols;

    mvaddch(y[0], x[0], '0');
    mvaddch(y[1], x[1], '3');
    mvaddch(y[0], x[1], '1');
    mvaddch(y[1], x[0], '2');

    draw_gui(10,10);

   

    /* done */

   // mvaddstr(maxlines, 0, "Press any key to quit");

    refresh();

    getch();
    endwin();

    exit(0);
}