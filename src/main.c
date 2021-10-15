/* triangle.c */

#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>

#include <main.h>

#include <gui.h>
#include <blocks.h>

#define ITERMAX 10000
int maxlines, maxcols;

int main(void)
{
    curs_set(FALSE);
    setlocale(LC_ALL, "");
    srand(time(NULL));

    /* initialize curses */

    initscr();
    cbreak();
    noecho();

    clear();

    

    //the update loop
    draw_gui(0, 0);
    refresh();

    Block b = initBlock(I);
    draw_block(b);
    refresh();

    //loop that updates the screen at a constant rate
    while(1)
    {
        usleep(16700);
        tick();
        update();

    }

    
    refresh();

    getch();
    endwin();

    exit(0);
}

void update(){
    maxlines = LINES - 1;
    maxcols = COLS - 1;
    draw_gui(0,0);

    refresh();
}

void tick(){
    
}