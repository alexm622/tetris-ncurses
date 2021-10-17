/* triangle.c */

#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>
#include <signal.h>

#include <main.h>

#include <gui.h>
#include <blocks.h>
#include <game.h>

int maxlines, maxcols;
Playfield* p;
WINDOW *tetris_win;
Block b;

void signal_callback_handler(int signum){
    endwin();
    freePlayfield(p);
    freeBlockElements(&b);
    exit(0);
}


int main(void)
{
    signal(SIGINT, signal_callback_handler);
    curs_set(FALSE);
    setlocale(LC_ALL, "");
    srand(time(NULL));

    /* initialize curses */

    initscr();
    cbreak();
    noecho();

    clear();

    

    

    //the update loop
    tetris_win = draw_gui(0, 0);
    keypad(tetris_win, true);
    nodelay(tetris_win, true);
    cbreak();
    refresh();

    b = initBlock(blockGenerator());
    p = initialize_playfield(WIDTH,HEIGHT);
    bool block_update = true;
    //loop that updates the screen at a constant rate
    while(1)
    {
        int dx,dy;
        bool drop = false;
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
        case ' ':
            drop = true;
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
            if(!bx){
                if(playfieldCollisionCheckX(b,p,dx)){
                    if(by || !playfieldCollisionCheckY(b,p,dy)){
                        addToPlayfield(&b, p);
                        b = initBlock(blockGenerator());
                    }
                }
            }
            block_update = false;
        }else{
            block_update = !updateBlock(b, p, dy, dx, drop);
            if(drop){
                addToPlayfield(&b, p);
                b = initBlock(blockGenerator());
            }
            drop = false;
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