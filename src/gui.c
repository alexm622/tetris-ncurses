#include <gui.h>

#include <curses.h>
#include <stdlib.h>

#include <blocks.h>

#define WIDTH 20
#define HEIGHT 40
#define XOFF 60
#define YOFF 2

void draw_gui(int x, int y){
    mvprintw(y, x," _______  _______  _______  ______    ___   _______ ");
    mvprintw(y+1, x,"|       ||       ||       ||    _ |  |   | |       |");
    mvprintw(y+2, x,"|_     _||    ___||_     _||   | ||  |   | |  _____|");
    mvprintw(y+3, x,"  |   |  |   |___   |   |  |   |_||_ |   | | |_____ ");
    mvprintw(y+4, x,"  |   |  |    ___|  |   |  |    __  ||   | |_____  |");
    mvprintw(y+5, x,"  |   |  |   |___   |   |  |   |  | ||   |  _____| |");
    mvprintw(y+6, x,"  |___|  |_______|  |___|  |___|  |_||___| |_______|");
    int cursorx = x + XOFF;
    int cursory = y + YOFF;
    for(int i = 0; i < HEIGHT + 2; i++){
        for(int j = 0; j < WIDTH + 2; j++){
            if(i == HEIGHT + 1 || i == 0){
                for(int k = 0; k < WIDTH + 2; k++){
                    if(k == 0 || k == WIDTH + 1){
                        mvaddch(cursory, cursorx, '|');
                        cursorx++;
                        continue;
                    }else{
                        mvaddch(cursory,cursorx, '#');
                        cursorx++;
                    }
                }
                break;
            }else{
                if(j == 0 || (j == WIDTH + 1)){
                    if((j == WIDTH + 1)){
                        cursorx++;
                    }
                    mvaddch(cursory, cursorx, '|');
                    continue;
                }
                cursorx++;
                
            }
            
        }
        cursorx = x + XOFF;
        cursory++;
    }
}

void draw_block(Block b){
    int num = b.num_pixels;
    for(int i = 0; i < num; i++){
        draw_pixel(b.blocks[i]);
    }
}

void draw_pixel(Pixel * p){
    if(p->empty){
        return;
    }
    mvaddch(p->y + YOFF + 1,p->x + XOFF + 1, '#');
}
