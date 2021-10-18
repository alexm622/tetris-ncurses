#ifndef BLOCKS_H
#define BLOCKS_H
#include <stdbool.h>
extern bool iBlock[1][4];
/**
 * @brief an enum of all the block types
 * 
 */
typedef enum{
    I,O,T,S,Z,L,J
}BLOCK;
/**
 * @brief the pixel object
 * 
 */
typedef struct pixel{
    bool empty;
    int x; /** the x position of the pixel*/
    int y; /** the y position of the pixel*/
}Pixel;
/**
 * @brief the block object
 * 
 */
typedef struct block{
    BLOCK b; /** the block enum name*/
    int num_pixels; /** the number of pixels in the block object */ // this might be unecessary, as it'll always be for
    Pixel ** pixels; /** all the pixels in the block */
}Block;
/**
 * @brief the whole playfield
 * 
 */
typedef struct playfield{
    Pixel *** field; /** a 2d array of pixel projects */
    int height; /** the height of the playfield*/
    int width; /** the width of the playfield*/
}Playfield;

Block initBlock(BLOCK b_type);
Pixel ** initL();
Pixel ** initJ();
Pixel ** initI();
Pixel ** initS();
Pixel ** initZ();
Pixel ** initO();
Pixel ** initT();

BLOCK blockGenerator();

void freeBlockElements(Block * b);
void freePlayfield(Playfield* p);
#endif