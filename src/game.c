#include <string.h>

#include <game.h>
#include <gui.h>

bool updateBlock(Block b, Playfield *p, int dy, int dx, bool drop) {

  bool out = playfieldCollisionCheck(b, p, dx, dy, drop);
  return out;
}
/**
 * @brief test to see if the block can be shifted on the x axis without leaving the playarea
 * 
 * @param b 
 * @param dx 
 * @return true 
 * @return false 
 */
bool shiftBlockX(Block b, int dx) {
  for (int i = 0; i < b.num_pixels; i++) {
    Pixel *p = b.pixels[i];
    if ((p->x + dx > WIDTH || p->x + dx < 0)) {
      return false;
    }
  }

  return true;
}
/**
 * @brief test to see if the block can be shifted dy units without leaving the playarea
 * 
 * @param b 
 * @param dy 
 * @return true 
 * @return false 
 */
bool shiftBlockY(Block b, int dy) {
  // find the lowest point pixel
  int array[b.num_pixels];
  int y_low_ind = 0;
  int lowy = b.pixels[0]->y;
  for (int i = 0; i < b.num_pixels; i++) {
    if (b.pixels[i]->y < lowy) {
      y_low_ind = i;
      lowy = b.pixels[i]->y;
    }
  }
  for (int i = 0; i < b.num_pixels; i++) {
    Pixel *p = b.pixels[(i + y_low_ind) % b.num_pixels];
    if ((p->y + dy >= HEIGHT)) {
      return false;
    }
  }
  return true;
}
/**
 * @brief add the block to the playfield
 * 
 * @param b 
 * @param p 
 */
void addToPlayfield(Block *b, Playfield *p) {
  int num_block = b->num_pixels;
  for (int i = 0; i < num_block; i++) {
    int x = b->pixels[i]->x;
    int y = b->pixels[i]->y;
    Pixel *pix = p->field[x][y];
    // we'll memcopy this instead of copying the register
    memcpy(pix, b->pixels[i], sizeof(struct pixel));
  }
  freeBlockElements(b);
}
// check this after regular bounds checking or it will segfault
/**
 * @brief check to see if the block collides with the playfield and is in bounds, take the drop value and the dx,dy, and the playfield as a pointer
 * 
 * @param b 
 * @param p 
 * @param dx 
 * @param dy 
 * @param drop 
 * @return true 
 * @return false 
 */
bool playfieldCollisionCheck(Block b, Playfield *p, int dx, int dy, bool drop) {
  if (drop) {
    int dy_n = 0; /** the new deltay which drops the block the lowest that it can go */
    for (int i = 0; i <= HEIGHT; i++) {
      bool out_y = shiftBlockY(b, i);
      if (!out_y) {
        //if cannot shift block any lower then we save the distance from the bottom to dy_n
        dy_n = i; 
        break;
      }
    }
    //now that we have the distance from the bottom we want to try and shift it down even more
    for (int i = 0; i < dy_n; i++) {
      bool pf_col_y = playfieldCollisionCheckY(b, p, i);
      if (!pf_col_y) {
        dy_n = i;
        break;
      }
    }
    //shift the block down as far as it can go
    for (int i = 0; i < b.num_pixels; i++) {
      Pixel *p = b.pixels[i];
      p->y += dy_n - 1;
    }
    return true;
  }

  bool out_x = shiftBlockX(b, dx); /** can the block be shifted the dx? */
  bool out_y = shiftBlockY(b, dy); /** can the block be shifted the dy?*/
  bool out = out_x && out_y; /** can the block be shifted the requested amount?*/
  bool pf_x /**can the block be shifted on the playfield x?*/, pf_y /**can the block be shifted on the playfield y*/; 
  //we need to test to see if the block is in bounds or else the program will segfault
  if (out_x) {
    //test to see if the block can be shifted on the x axis
    pf_x = playfieldCollisionCheckX(b, p, dx);
    //if the block can be shifted in the desired way we will drop it
    if (pf_x) {
      for (int i = 0; i < b.num_pixels; i++) {
        Pixel *p = b.pixels[i];
        p->x += dx;
      }
    }
    //and operation with pf_x and out
    out &= pf_x;
  }
  //we need to test this so the program doesn't segfault
  if (out_y) {
    //test to see if the block can be shifted on the y axis
    pf_y = playfieldCollisionCheckY(b, p, dy);
    //if it can then shift it
    if (pf_y) {
      for (int i = 0; i < b.num_pixels; i++) {
        Pixel *p = b.pixels[i];
        p->y += dy;
      }
    }
    //and operation with pf_x and out
    out &= pf_y;
  }
  //return whether or not the block was shifted
  return out;
}
/**
 * @brief check to see if the block will intersect with the playfield when shifted horizontally dx blocks
 * 
 * @param b 
 * @param p 
 * @param dx 
 * @return true 
 * @return false 
 */
bool playfieldCollisionCheckX(Block b, Playfield *p, int dx) {
  for (int i = 0; i < b.num_pixels; i++) {
    Pixel *pix = b.pixels[i];
    if (!p->field[pix->x + dx][pix->y]->empty) {
      return false;
    }
  }
  return true;
}
/**
 * @brief see if the block b collides with the playfield when shifted down deltaY blocks
 * 
 * @param b 
 * @param p 
 * @param dy 
 * @return true 
 * @return false 
 */
bool playfieldCollisionCheckY(Block b, Playfield *p, int dy) {
  for (int i = 0; i < b.num_pixels; i++) {
    Pixel *pix = b.pixels[i];
    if (!p->field[pix->x][pix->y + dy]->empty) {
      return false;
    }
  }
  return true;
}
/**
 * @brief checks to see if the gameover has been achieved
 * 
 * @param b 
 * @return true 
 * @return false 
 */
bool gameOverCheck(Block b) {
  bool shift = shiftBlockY(b, 1);
  if (b.pixels[0]->y < 20) {
    return true && !shift;
  }
  return false;
}
