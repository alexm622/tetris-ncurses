#include <blocks.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool iBlock[1][4] = {{true,true,true,true}};

bool oBlock[2][2] = {
    {true, true},
    {true, true}
};
bool tBlock[3][2] = {
    {true,false},
    {true,true,},
    {true,false}
};
bool zBlock[3][2] = {
    {false,true},
    {true,true},
    {true,false}
};
bool sBlock[3][2] = {
    {true,false},
    {true,true},
    {false,true}
};
bool lBlock[2][3] = {
    {true,true,true},
    {true,false,false},
    
};
bool jBlock[2][3] = {
    {true,false,false},
    {true,true,true}
};

Block initBlock(BLOCK b_type){
    Block out;
    out.num_pixels = 4;
    out.b = b_type;
    out.blocks = initL();
    return out;
}

Pixel ** initL(){
    Pixel ** out = calloc(4, sizeof(struct Pixel*));
    Pixel * p = malloc(sizeof(struct Pixel));
    for(int i = 0; i < 3; i++){
        p->empty = false;
        p->x = i;
        p->y = 0;
        out[i] = p;
        p = calloc(1, sizeof(struct Pixel));
    }
    p->empty = false;
    p->x=0;
    p->y=1;
    out[3] = p;
    return out;


}