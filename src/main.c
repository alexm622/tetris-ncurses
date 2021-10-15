/* triangle.c */

#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>

#include <main.h>

#include <gui.h>
#include <blocks.h>
#include <game.h>

int maxlines, maxcols;
Playfield* p;

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

    WINDOW *tetris_win;
    

    

    //the update loop
    tetris_win = draw_gui(0, 0);
    keypad(tetris_win, true);
    nodelay(tetris_win, true);
    cbreak();
    refresh();

    Block b = initBlock(blockGenerator());
    p = initialize_playfield(WIDTH,HEIGHT);
    bool block_update;
    //loop that updates the screen at a constant rate
    while(1)
    {
        int dx,dy;
        int down = wgetch(tetris_win);
        switch (down)
        {
        case KEY_UP:
            dy = -1;
            break;
        case KEY_DOWN:
            dy = 2;
            break;
        case KEY_LEFT:
            dx = -1;
            break;
        case KEY_RIGHT:
            dx = 1;
            break;
        default:
            dy = 1;
            dx = 0;
            break;
        }
        tick();
        draw_block(b);
        update();
        flushinp();
        usleep(100000);
        if(block_update){
            bool bx = !shiftBlockX(b, dx);
            bool by = !shiftBlockY(b, dy);
            if(by){
                addToPlayfield(&b, p);
                b = initBlock(blockGenerator());
            }
            block_update = false;
        }else{
            block_update = !updateBlock(b, dy, dx);
        }
        
        clear();

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
    draw_playfield(p);

    refresh();
}

void tick(){
    
}