#include <string.h>

#include <game.h>
#include <gui.h>

bool updateBlock(Block b, int dy, int dx){
    
    bool out = shiftBlockY(b, dy) && shiftBlockX(b, dx);
    return out;
}

bool shiftBlockX(Block b, int dx){
    for(int i = 0; i<b.num_pixels; i++){
        Pixel * p = b.blocks[i];
        if((p->x + dx > WIDTH || p->x + dx < 0)){
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
    //find the lowest point pixel
    int array[b.num_pixels];
    int y_low_ind = 0;
    int lowy = b.blocks[0]->y;
    for(int i = 0; i < b.num_pixels; i++){
        if(b.blocks[i]->y < lowy){
            y_low_ind = i;
            lowy = b.blocks[i]->y;
        }
    }
    for(int i = 0; i<b.num_pixels; i++){
        Pixel * p = b.blocks[(i+y_low_ind)%b.num_pixels];
        if((p->y + dy >= HEIGHT)){
            return false;
        }
    }
    for(int i = 0; i<b.num_pixels; i++){
        Pixel * p = b.blocks[i];
        p->y += dy;
    }
    return true;
}

void addToPlayfield(Block *b, Playfield* p){
    int num_block = b->num_pixels;
    for(int i =0; i < num_block; i++){
        int x = b->blocks[i]->x;
        int y = b->blocks[i]->y;
        Pixel* pix = p->field[x][y];
        //we'll memcopy this instead of copying the register
        memcpy(pix, b->blocks[i], sizeof(struct pixel *));
    }
}