#include <blocks.h>


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool iBlock[1][4] = {{true, true, true, true}};

bool oBlock[2][2] = {{true, true}, {true, true}};
bool tBlock[3][2] = {{true, false},
                     {
                         true,
                         true,
                     },
                     {true, false}};
bool zBlock[3][2] = {{false, true}, {true, true}, {true, false}};
bool sBlock[3][2] = {{true, false}, {true, true}, {false, true}};
bool lBlock[2][3] = {
    {true, true, true},
    {true, false, false},

};
bool jBlock[2][3] = {{true, false, false}, {true, true, true}};

Block initBlock(BLOCK b_type) {
  Block out;
  out.num_pixels = 4;
  out.b = b_type;
  switch (b_type)
  {
  case I:
    out.blocks = initI();
    break;
  case J:
    out.blocks = initJ();
    break;
  case L:
    out.blocks = initL();
    break;
  case O:
    out.blocks = initO();
    break;
  case S:
    out.blocks = initS();
    break;
  case Z:
    out.blocks = initZ();
    break;
  case T:
    out.blocks = initT();
    break;
  default:
    out.blocks = initO();
    break;
  }
  return out;
}

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
Pixel **initS() {
  struct pixel **out = calloc(4, sizeof(struct pixel *));
  struct pixel *p = malloc(sizeof(struct pixel));
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      p->empty = false;
      p->x = i + j;
      p->y = 1 - i;
      out[i * 2 + j] = p;
      p = malloc(sizeof(struct pixel));
    }
  }
  return out;
}
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

void print_pix(Pixel **p, int size) {
  for (int i = 0; i < size; i++) {
    printf("%i,", p[i]->x);
    printf("%i\n", p[i]->y);
  }
}
