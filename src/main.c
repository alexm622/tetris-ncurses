/* triangle.c */

#include <curses.h>
#include <locale.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <main.h>

#include <blocks.h>
#include <game.h>
#include <gui.h>

#define _BSD_SOURCE
int maxlines, maxcols;
Playfield *p;
WINDOW *tetris_win;
Block b;
int score = 0;
bool drop = false;
bool block_update = true;
bool go = false;
int dx, dy;
int level = 0;
/**
 * @brief handle the ctrl+c from user and clear memory on ctrl-c
 *
 * @param signum
 */
void signal_callback_handler(int signum) {
  endwin();
  freePlayfield(p);
  freeBlockElements(&b);
  exit(0);
}

void signal_term_handler(int signum) {
  endwin();
  freePlayfield(p);
  freeBlockElements(&b);
  // do something for game over eventually
  exit(0);
}

/**
 * @brief the main entry point of the program
 *
 * @return int return code
 */
int main(void) {
  signal(SIGINT, signal_callback_handler);
  curs_set(FALSE);
  setlocale(LC_ALL, "");
  srand(time(NULL));

  /* initialize curses */

  initscr();
  cbreak();
  noecho();

  clear();

  // the update loop
  tetris_win = draw_gui(0, 0);
  keypad(tetris_win, true);
  nodelay(tetris_win, true);
  cbreak();
  refresh();

  b = initBlock(O); // blockGenerator());
  p = initialize_playfield(WIDTH, HEIGHT);
  // loop that updates the screen at a constant rate
  while (1) {
    int down = wgetch(tetris_win);
    switch (down) {
    case KEY_UP:
      dy = -1;
      break;
    case KEY_DOWN:
      dy = 2;
      break;
    case KEY_LEFT:
      dx = -1;
      break;
    case KEY_RIGHT:
      dx = 1;
      break;
    case ' ':
      drop = true;
      break;
    default:
      dy = 1;
      dx = 0;
      break;
    }
    tick();
    if (go) {
      break;
    }
    update();
    flushinp();
    // TODO make this use a deltatime variant?
    // or implement nanosleep()
    usleep(100000);
    // TODO move this to its own method, and move it into the tick function

  }
  refresh();

  getch();
  endwin();

  signal_callback_handler(0);
}
/**
 * @brief the update method that is called to redraw the gui
 *
 */
void update() {
  maxlines = LINES - 1;
  maxcols = COLS - 1;
  draw_gui(0, 0);
  draw_score(score);
  draw_playfield(p);
  draw_block(b);

  refresh();
}
void tick() {
  tick_gamefield();
  score += inc_score(checkPlayfield(p), level);
}

void tick_gamefield() {
  if (block_update) {
    bool bx = !shiftBlockX(b, dx);
    bool by = !shiftBlockY(b, dy);

    if (!bx) {
      if (playfieldCollisionCheckX(b, p, dx)) {
        if (by || !playfieldCollisionCheckY(b, p, dy)) {
          if (go) {
            return;
          }
          addToPlayfield(&b, p);
          b = initBlock(O); // blockGenerator());
        }
      }
    }
    block_update = false;
  } else {
    block_update = !updateBlock(b, p, dy, dx, drop);
    if (drop) {
      go = gameOverCheck(b);
      if (go) {
        return;
      }
      addToPlayfield(&b, p);
      b = initBlock(O); // blockGenerator());
    }
    drop = false;
  }
  clear();
  return;
}
