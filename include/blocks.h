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
typedef struct{
    BLOCK b;
    int w;
    int h;
    int** block;
}Block;

#endif