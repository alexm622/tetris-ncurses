#include <string.h>

#include <game.h>
#include <gui.h>

bool updateBlock(Block b, Playfield* p, int dy, int dx, bool drop){
    
    
    bool out = playfieldCollisionCheck(b, p, dx, dy, drop);
    return out;
}

bool shiftBlockX(Block b, int dx){
    for(int i = 0; i<b.num_pixels; i++){
        Pixel * p = b.pixels[i];
        if((p->x + dx > WIDTH || p->x + dx < 0)){
            return false;
        }
    }
    
    return true;
}

bool shiftBlockY(Block b, int dy){
    //find the lowest point pixel
    int array[b.num_pixels];
    int y_low_ind = 0;
    int lowy = b.pixels[0]->y;
    for(int i = 0; i < b.num_pixels; i++){
        if(b.pixels[i]->y < lowy){
            y_low_ind = i;
            lowy = b.pixels[i]->y;
        }
    }
    for(int i = 0; i<b.num_pixels; i++){
        Pixel * p = b.pixels[(i+y_low_ind)%b.num_pixels];
        if((p->y + dy >= HEIGHT)){
            return false;
        }
    }
    return true;
}

void addToPlayfield(Block *b, Playfield* p){
    int num_block = b->num_pixels;
    for(int i =0; i < num_block; i++){
        int x = b->pixels[i]->x;
        int y = b->pixels[i]->y;
        Pixel* pix = p->field[x][y];
        //we'll memcopy this instead of copying the register
        memcpy(pix, b->pixels[i], sizeof(struct pixel *));
    }
    freeBlockElements(b);
}
//check this after regular bounds checking or it will segfault

bool playfieldCollisionCheck(Block b, Playfield* p, int dx, int dy, bool drop){
    if(drop){
        int dy_n = 0;
        for(int i = 0; i <=  HEIGHT; i++){
            bool out_y = shiftBlockY(b, i);        
            if(!out_y){
                dy_n = i;
                break;
            }
        }
        for(int i = 0; i < dy_n; i++){
            bool pf_col_y = playfieldCollisionCheckY(b,p,i);
            if(!pf_col_y){
                dy_n = i;
                break;
            }
        }
        for(int i = 0; i<b.num_pixels; i++){
            Pixel * p = b.pixels[i];
            p->y += dy_n-1;
        }
        return true;
    }
    bool out_x = shiftBlockX(b,dx);
    bool out_y = shiftBlockY(b, dy);
    bool out = out_x && out_y;
    bool pf_x, pf_y;
    if(out_x){
        pf_x = playfieldCollisionCheckX(b, p, dx);
        if(pf_x){
            for(int i = 0; i<b.num_pixels; i++){
                Pixel * p = b.pixels[i];
                p->x += dx;
            }
        }
        out &= pf_x;
        
    }
    if(out_y){
        pf_y = playfieldCollisionCheckY(b,p,dy);
        if(pf_y){
            for(int i = 0; i<b.num_pixels; i++){
                Pixel * p = b.pixels[i];
                p->y += dy;
            }
        }
        out &= pf_y;
    }
    return out;
}
bool playfieldCollisionCheckX(Block b, Playfield* p, int dx){
    for(int i = 0; i<b.num_pixels; i++){
        Pixel * pix = b.pixels[i];
        if(!p->field[pix->x+dx][pix->y]->empty){
            return false;
        }
    }
    return true;
}

bool playfieldCollisionCheckY(Block b, Playfield* p, int dy){
    for(int i = 0; i<b.num_pixels; i++){
        Pixel * pix = b.pixels[i];
        if(!p->field[pix->x][pix->y+dy]->empty){
            return false;
        }
    }
    return true;
}
