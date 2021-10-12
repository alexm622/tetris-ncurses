#include <gui.h>

#include <curses.h>
#include <stdlib.h>


void draw_gui(int x, int y){
    mvprintw(y, x," _______  _______  _______  ______    ___   _______ ");
    mvprintw(y+1, x,"|       ||       ||       ||    _ |  |   | |       |");
    mvprintw(y+2, x,"|_     _||    ___||_     _||   | ||  |   | |  _____|");
    mvprintw(y+3, x,"  |   |  |   |___   |   |  |   |_||_ |   | | |_____ ");
    mvprintw(y+4, x,"  |   |  |    ___|  |   |  |    __  ||   | |_____  |");
    mvprintw(y+5, x,"  |   |  |   |___   |   |  |   |  | ||   |  _____| |");
    mvprintw(y+6, x,"  |___|  |_______|  |___|  |___|  |_||___| |_______|");

}
