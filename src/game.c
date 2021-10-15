#include <game.h>
#include <gui.h>

bool updateBlock(Block b){
    shiftBlockY(b, 1);
}

bool shiftBlockX(Block b, int dx){
    for(int i = 0; i<b.num_pixels; i++){
        Pixel * p = b.blocks[i];
        if((p->x + dx > WIDTH || p->y + dx < 0)){
            return false;
        }
    }
    for(int i = 0; i<b.num_pixels; i++){
        Pixel * p = b.blocks[i];
        p->x += dx;
    }
    return true;
}

bool shiftBlockY(Block b, int dy){
    for(int i = 0; i<b.num_pixels; i++){
        Pixel * p = b.blocks[i];
        if((p->y + dy > HEIGHT-1 || p->y + dy < 0 )){
            return false;
        }
    }
    for(int i = 0; i<b.num_pixels; i++){
        Pixel * p = b.blocks[i];
        p->y += dy;
    }
    return true;
}
