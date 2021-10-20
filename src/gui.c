#include <gui.h>

#include <curses.h>
#include <stdlib.h>

#include <blocks.h>
/**
 * @brief draw the tetris gui
 *
 * @param x x offset
 * @param y y offset
 * @return WINDOW*
 */
WINDOW *draw_gui(int x, int y) {
  mvprintw(y, x, " _______  _______  _______  ______    ___   _______ ");
  mvprintw(y + 1, x, "|       ||       ||       ||    _ |  |   | |       |");
  mvprintw(y + 2, x, "|_     _||    ___||_     _||   | ||  |   | |  _____|");
  mvprintw(y + 3, x, "  |   |  |   |___   |   |  |   |_||_ |   | | |_____ ");
  mvprintw(y + 4, x, "  |   |  |    ___|  |   |  |    __  ||   | |_____  |");
  mvprintw(y + 5, x, "  |   |  |   |___   |   |  |   |  | ||   |  _____| |");
  mvprintw(y + 6, x, "  |___|  |_______|  |___|  |___|  |_||___| |_______|");
  WINDOW *tetris_win;
  tetris_win = newwin(HEIGHT, WIDTH, XOFF, YOFF);
  // draw the box
  int cursorx = x + XOFF;
  int cursory = y + YOFF;
  for (int i = 0; i < HEIGHT + 2; i++) {
    for (int j = 0; j < WIDTH + 2; j++) {
      if (i == HEIGHT + 1 || i == 0) {
        for (int k = 0; k < WIDTH + 2; k++) {
          if (k == 0 || k == WIDTH + 1) {
            mvaddch(cursory, cursorx, '|');
            cursorx++;
            continue;
          } else {
            mvaddch(cursory, cursorx, '#');
            cursorx++;
          }
        }
        break;
      } else {
        if (j == 0 || (j == WIDTH + 1)) {
          if ((j == WIDTH + 1)) {
            cursorx++;
          }
          mvaddch(cursory, cursorx, '|');
          continue;
        }
        cursorx++;
      }
    }
    cursorx = x + XOFF;
    cursory++;
  }
  return tetris_win;
}
/**
 * @brief draw block b
 *
 * @param b the block
 */
void draw_block(Block b) {
  int num = b.num_pixels;
  for (int i = 0; i < num; i++) {
    draw_pixel(b.pixels[i]);
  }
}
/**
 * @brief draw a singular pixel
 *
 * @param p the pixel pointer
 */
void draw_pixel(Pixel *p) {
  if (p->empty) {
    return;
  }
  mvaddwstr(p->y + YOFF + 1, p->x + XOFF + 1, L"▯");
}
/**
 * @brief draw the score on the screen
 *
 * @param score the current score
 */
void draw_score(int score) {
  mvprintw(HEIGHT + YOFF + 2, XOFF, "Score: %d", score);
}

/**
 * @brief draw the whole playfield
 *
 * @param pf the playfield pointer
 */
void draw_playfield(Playfield *pf) {
  for (int i = 0; i < pf->width; i++) {
    for (int j = 0; j < pf->height; j++) {
      draw_pixel(pf->field[i][j]);
    }
  }
}
/**
 * @brief initialize the playfield as an empty object
 *
 * @param width the width of the playfield
 * @param height the height of the playfield
 * @return Playfield*
 */
Playfield *initialize_playfield(int width, int height) {
  // allocate memory for the base playfield pointer
  Playfield *pf = malloc(sizeof(struct playfield));
  pf->width = width;
  pf->height = height;
  // allocate the memory for the 2d pixel array first dimension
  pf->field = malloc(sizeof(struct pixel **) * width);
  for (int i = 0; i < width; i++) {
    // allocate memory for the second dimension
    pf->field[i] = malloc(sizeof(struct pixel *) * height);
    for (int j = 0; j < height; j++) {
      // make new pixels
      Pixel *p = malloc(sizeof(struct pixel));
      p->x = i;
      p->y = j;
      p->empty = true;
      pf->field[i][j] = p;
    }
  }
  // return the playfield
  return pf;
}
