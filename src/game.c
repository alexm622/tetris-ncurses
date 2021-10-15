#include <game.h>
#include <gui.h>

bool updateBlock(Block b, int dy, int dx){
    shiftBlockY(b, dy);
    shiftBlockX(b, dx);

}

bool shiftBlockX(Block b, int dx){
    for(int i = 0; i<b.num_pixels; i++){
        Pixel * p = b.blocks[i];
        if((p->x + dx >= WIDTH || p->x + dx < 0)){
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
        if((p->y + dy >= HEIGHT || p->y + dy < 0 )){
            return false;
        }
    }
    for(int i = 0; i<b.num_pixels; i++){
        Pixel * p = b.blocks[i];
        p->y += dy;
    }
    return true;
}
