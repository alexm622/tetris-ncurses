/* triangle.c */

#include <curses.h>
#include <stdlib.h>
#include <time.h>

#include <gui.h>
#include <blocks.h>

#define ITERMAX 10000

int main(void)
{
    int maxlines, maxcols;
    srand(time(NULL));

    /* initialize curses */

    initscr();
    cbreak();
    noecho();

    clear();

    maxlines = LINES - 1;
    maxcols = COLS - 1;

    draw_gui(0,0);
    BLOCK newblock = I;
    Block b = initBlock(newblock);
    draw_block(b);

    refresh();

    getch();
    endwin();

    exit(0);
}