#ifndef BLOCKS_H
#define BLOCKS_H
#include <stdbool.h>
extern bool iBlock[1][4];
extern bool oBlock[2][2];
extern bool tBlock[3][2];
extern bool sBlock[3][2];
extern bool zBlock[3][2];
extern bool lBlock[2][3];
extern bool jBlock[2][3];
typedef enum{
    I,O,T,S,Z,L,J
}BLOCK;
typedef struct pixel{
    bool empty;
    int x; //relative offset
    int y; //relative position
}Pixel;

typedef struct block{
    BLOCK b;
    int num_pixels;
    Pixel ** pixels;
}Block;

typedef struct playfield{
    Pixel *** field;
    int height;
    int width; 
}Playfield;

Block initBlock(BLOCK b_type);
Pixel ** initL();
Pixel ** initJ();
Pixel ** initI();
Pixel ** initS();
Pixel ** initZ();
Pixel ** initO();
Pixel ** initT();

void print_pix(Pixel** p, int size);

BLOCK blockGenerator();

void freeBlockElements(Block * b);
#endif