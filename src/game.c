/* License generated by licensor(https://github.com/Marvin9/licensor).

 alexm622/tetris-ncurses
 Copyright (C) 2021  Alexander Comeau

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <game.h>
#include <gui.h>

bool updateBlock(Block b, Playfield *p, int dy, int dx, bool drop) {

  bool out = playfieldCollisionCheck(b, p, dx, dy, drop);
  return out;
}
/**
 * @brief test to see if the block can be shifted on the x axis without leaving
 * the playarea
 *
 * @param b
 * @param dx
 * @return true
 * @return false
 */
bool shiftBlockX(Block b, int dx) {
  for (int i = 0; i < b.num_pixels; i++) {
    Pixel *p = b.pixels[i];
    if ((p->x + dx >= WIDTH || p->x + dx < 0)) {
      return false;
    }
  }
  return true;
}
/**
 * @brief test to see if the block can be shifted dy units without leaving the
 * playarea
 *
 * @param b
 * @param dy
 * @return true
 * @return false
 */
bool shiftBlockY(Block b, int dy) {
  // find the lowest point pixel
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
  bool gameover = false;
  for (int i = 0; i < num_block; i++) {
    int x = b->pixels[i]->x;
    int y = b->pixels[i]->y;
    Pixel *pix = p->field[x][y];
    // we'll memcopy this instead of copying the register
    if (y <= 1) {
      gameover = true;
      break;
    }
    memcpy(pix, b->pixels[i], sizeof(struct pixel));
  }
  if (gameover) {
    raise(SIGTERM);
    return;
  }
  freeBlockElements(b);
}
// check this after regular bounds checking or it will segfault
/**
 * @brief check to see if the block collides with the playfield and is in
 * bounds, take the drop value and the dx,dy, and the playfield as a pointer
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
    int dy_n =
        0; /** the new deltay which drops the block the lowest that it can go */
    for (int i = 0; i <= p->height; i++) {
      bool out_y = shiftBlockY(b, i);
      if (!out_y) {
        // if cannot shift block any lower then we save the distance from the
        // bottom to dy_n
        dy_n = i;
        break;
      }
    }
    // now that we have the distance from the bottom we want to try and shift it
    // down even more
    for (int i = 0; i < dy_n; i++) {
      bool pf_col_y = playfieldCollisionCheckY(b, p, i);
      if (!pf_col_y) {
        dy_n = i;
        break;
      }
    }
    // shift the block down as far as it can go
    for (int i = 0; i < b.num_pixels; i++) {
      Pixel *pix = b.pixels[i];
      pix->y += dy_n - 1;
    }
    return true;
  }

  bool out_x = shiftBlockX(b, dx); /** can the block be shifted the dx? */
  bool out_y = shiftBlockY(b, dy); /** can the block be shifted the dy?*/
  bool out =
      out_x && out_y; /** can the block be shifted the requested amount?*/
  bool pf_x /**can the block be shifted on the playfield x?*/,
      pf_y /**can the block be shifted on the playfield y*/;
  // we need to test to see if the block is in bounds or else the program will
  // segfault
  if (out_x) {
    // test to see if the block can be shifted on the x axis
    pf_x = playfieldCollisionCheckX(b, p, dx);
    // if the block can be shifted in the desired way we will drop it
    if (pf_x) {
      for (int i = 0; i < b.num_pixels; i++) {
        Pixel *pix = b.pixels[i];
        pix->x += dx;
      }
    }
    // and operation with pf_x and out
    out &= pf_x;
  }
  if (!out_x) {
    gameOverCheck(b);
  }
  // we need to test this so the program doesn't segfault
  if (out_y) {
    // test to see if the block can be shifted on the y axis
    pf_y = playfieldCollisionCheckY(b, p, dy);
    // if it can then shift it
    if (pf_y) {
      for (int i = 0; i < b.num_pixels; i++) {
        Pixel *pix = b.pixels[i];
        pix->y += dy;
      }
    } else {
      gameOverCheck(b);
    }
    // and operation with pf_x and out
    out &= pf_y;
  }
  // return whether or not the block was shifted
  return out;
}
/**
 * @brief check to see if the block will intersect with the playfield when
 * shifted horizontally dx blocks
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
 * @brief see if the block b collides with the playfield when shifted down
 * deltaY blocks
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
  if (b.pixels[0]->y < 5) {
    return true && !shift;
  }
  return false;
}
/**
 *
 * @brief check the playfield for lines and then remove and drow those lines
 *
 * @param p
 *
 * @return int lines cleared
 *
 */
int checkPlayfield(Playfield *p) {
  int rowsremoved = 0;
  for (int i = 0; i < p->height; i++) {
    bool full = false;
    for (int j = 0; j < p->width; j++) {
      Pixel *pix = p->field[j][i];
      if (pix->empty) {
        full = false;
        break;
      }
      full = true;
    }
    if (full) {
      removeRow(p, i);
      rowsremoved++;
      if (i > 0) {
        moveRowsDown(p, i);
      }
    }
  }
  return rowsremoved;
}
/**
 * @brief remove row at index row
 *
 * @param p
 * @param row the row to be removed
 *
 */
void removeRow(Playfield *p, int row) {
  for (int i = 0; i < p->width; i++) {
    p->field[i][row]->empty = true;
  }
}
/**
 *@brief move all rows down starting in the position of lastrow
 *
 *@param lastrow the empty row
 *@param p
 *
 */
void moveRowsDown(Playfield *p, int lastrow) {
  // if the row is row 0 (the top) then there is nothing to move downwards
  if (lastrow == 0) {
    return;
  }
  for (int i = lastrow - 1; i > 0; i--) {
    for (int j = 0; j < p->width; j++) {
      p->field[j][i + 1]->empty = p->field[j][i]->empty;
      p->field[j][i]->empty = true;
    }
  }
}

int inc_score(int num_rows, int level) {
  switch (num_rows) {
  case 0:
    return 0;
  case 1:
    return 40 * (level + 1);
  case 2:
    return 100 * (level + 1);
  case 3:
    return 300 * (level + 1);
  case 4:
    return 1200 * (level + 1);
  default:
    return 0;
  }
}
/**
 *@brief rotate block b rotation * 90 degrees clockwise
 *
 *@param b block to be rotated
 *
 * @param rotation the number of times to rotate 90 degrees, positive for
 *clockwise negative for cclockwise
 */
void rotateBlock(Block *b, int rotation) {
  // rotate based of a matrix of width = width of the block and the height =
  // height of the stored block
  int width /** the width of the block */, height; /** height of the block */
  int least = 0, most = 0;

  for (int i = 0; i < 4; i++) {
    least = (least > b->pixels[i]->x) ? least : b->pixels[i]->x;
    most = (most < b->pixels[i]->x) ? most : b->pixels[i]->x;
  }
  int leastx = least; /** the top left x corner */
  width = most - least;
  for (int i = 0; i < 4; i++) {
    least = (least > b->pixels[i]->y) ? least : b->pixels[i]->y;
    most = (most < b->pixels[i]->y) ? most : b->pixels[i]->y;
  }
  int leasty = least; /** the top left y corner */
  height = most - least;
  // demensions of the matrix are width and height (x,y)
  // the final matrix will be height, width (x, y)
  Pixel **start_matrix = malloc(width * sizeof(struct pixel *));
  // allocate memory for start matrix
  for (int i = 0; i < width; i++) {
    start_matrix[i] = calloc(height, sizeof(struct pixel));
  }
  Pixel **end_matrix = malloc(height * sizeof(struct pixel *));
  // allocate memory for end matrix
  for (int i = 0; i < height; i++) {
    end_matrix[i] = calloc(width, sizeof(struct pixel));
  }
  // initialize start matrix with coordinates
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      start_matrix[i][j].x = i + leastx;
      start_matrix[i][j].y = i + leasty;
      start_matrix[i][j].empty = true;
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      end_matrix[i][j].x = i + leastx;
      end_matrix[i][j].y = i + leasty;
      end_matrix[i][j].empty = true;
    }
  }

  for (int i = 0; i < 4; i++) {
    Pixel *p = b->pixels[i];
    start_matrix[p->x - leastx][p->y - leasty].empty = false;
    start_matrix[p->x - leastx][p->y - leasty].x = p->x;
    start_matrix[p->x - leastx][p->y - leasty].y = p->y;
  }

  // turn the rotation into a positive value
  while (rotation < 0) {
    rotation += 4;
  }

  bool start_or_end = false;

  // rotate the matrix;
  for (int rot = 0; rot < rotation; rot++) {
    if (rot % 2 == 0) {
      start_or_end = false;
      for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
          end_matrix[j][i].empty = start_matrix[i][j].empty;
        }
      }
    } else {
      start_or_end = true;
      for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
          start_matrix[j][i].empty = end_matrix[i][j].empty;
        }
      }
    }
  }

  // map start or end to the pixels in the block
  int loc = 0;
  for (int i = 0; i < (start_or_end) ? width : height; i++) {
    for (int j = 0; j < (start_or_end) ? height : width; j++) {
      if (((start_or_end) ? end_matrix : start_matrix)[i][j].empty) {
        b->pixels[loc]->x =
            ((start_or_end) ? end_matrix : start_matrix)[i][j].x;
        b->pixels[loc]->y =
            ((start_or_end) ? end_matrix : start_matrix)[i][j].y;
        loc++;
      }
    }
  }
  return;
}
