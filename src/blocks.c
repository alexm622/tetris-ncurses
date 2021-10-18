#include <blocks.h>

#include <gui.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief create a new block pointer/object
 * 
 * @param b_type the block type as an enum
 * @return Block 
 */
Block initBlock(BLOCK b_type) {
  Block out;
  out.num_pixels = 4;
  out.b = b_type;
  switch (b_type)
  {
  case I:
    out.pixels = initI();
    break;
  case J:
    out.pixels = initJ();
    break;
  case L:
    out.pixels = initL();
    break;
  case O:
    out.pixels = initO();
    break;
  case S:
    out.pixels = initS();
    break;
  case Z:
    out.pixels = initZ();
    break;
  case T:
    out.pixels = initT();
    break;
  default:
    out.pixels = initO();
    break;
  }
  return out;
}
/**
 * @brief init the block L
 * 
 * @return Pixel** 
 */
Pixel **initL() {
  struct pixel **out = calloc(4, sizeof(struct pixel *));
  struct pixel *p;
  for (int i = 0; i < 3; i++) {
    p = malloc(sizeof(struct pixel));
    p->empty = false;
    p->x = i;
    p->y = 0;
    out[i] = p;
  }
  p = malloc(sizeof(struct pixel));
  p->empty = false;
  p->x = 0;
  p->y = 1;
  out[3] = p;
  return out;
}
/**
 * @brief init the block J
 * 
 * @return Pixel** 
 */
Pixel **initJ() {
  struct pixel **out = calloc(4, sizeof(struct pixel *));
  struct pixel *p;
  for (int i = 0; i < 3; i++) {
    p = malloc(sizeof(struct pixel));
    p->empty = false;
    p->x = i;
    p->y = 1;
    out[i] = p;
  }
  p = malloc(sizeof(struct pixel));
  p->empty = false;
  p->x = 0;
  p->y = 0;
  out[3] = p;
  return out;
}
/**
 * @brief init the block I
 * 
 * @return Pixel** 
 */
Pixel **initI() {
  struct pixel **out = calloc(4, sizeof(struct pixel *));
  struct pixel *p;
  for (int i = 0; i < 4; i++) {
    p = malloc(sizeof(struct pixel));
    p->empty = false;
    p->x = 0;
    p->y = i;
    out[i] = p;
  }
  return out;
}
/**
 * @brief init the block S
 * 
 * @return Pixel** 
 */
Pixel **initS() {
  struct pixel **out = calloc(4, sizeof(struct pixel *));
  struct pixel *p;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      p = malloc(sizeof(struct pixel));
      p->empty = false;
      p->x = i + j;
      p->y = 1 - i;
      out[i * 2 + j] = p;
    }
  }
  return out;
}
/**
 * @brief init the block Z
 * 
 * @return Pixel** 
 */
Pixel **initZ() {
  struct pixel **out = calloc(4, sizeof(struct pixel *));
  struct pixel *p;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      p = malloc(sizeof(struct pixel));
      p->empty = false;
      p->x = i + j;
      p->y = i;
      out[i * 2 + j] = p;
    }
  }
  return out;
}
/**
 * @brief init the block O
 * 
 * @return Pixel** 
 */
Pixel **initO() {
  struct pixel **out = calloc(4, sizeof(struct pixel *));
  struct pixel *p;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      p = malloc(sizeof(struct pixel));
      p->empty = false;
      p->x = j;
      p->y = i;
      out[i * 2 + j] = p;
    }
  }
  return out;
}
/**
 * @brief init a block of type T
 * 
 * @return Pixel** 
 */
Pixel **initT() {
  struct pixel **out = calloc(4, sizeof(struct pixel *));
  struct pixel *p;
  for (int i = 0; i < 3; i++) {
    p = malloc(sizeof(struct pixel));
    p->empty = false;
    p->x = i;
    p->y = 0;
    out[i] = p;
  }
  p = malloc(sizeof(struct pixel));
  p->empty = false;
  p->x = 1;
  p->y = 1;
  out[3] = p;
  return out;
}
/**
 * @brief generate a random block
 * 
 * @return BLOCK 
 */
BLOCK blockGenerator(){
  int r = rand();
  r %= 7;
  switch (r)
  {
  case 0:
    return I;
  case 1:
    return J;
  case 2:
    return L;
  case 3:
    return O;
  case 4:
    return S;
  case 5:
    return Z;
  case 6:
    return T;
  default:
    return O;
    break;
  }
}
/**
 * @brief free all the elements/pixels in block b
 * 
 * @param b 
 */
void freeBlockElements(Block * b){
  int num_pixels = b->num_pixels;
  for(int i = 0; i < num_pixels; i++){
    free(b->pixels[i]);
  }
  free(b->pixels);
}
/**
 * @brief free the playfield
 * 
 * @param p the playfield object as a pointer
 */
void freePlayfield(Playfield * p){
  for(int i = 0; i< WIDTH; i++){
    //free whole row on column i
    for(int j = 0; j < HEIGHT; j++){
      free(p->field[i][j]);
    }
    free(p->field[i]);
  }
  free(p->field);
  free(p);
}