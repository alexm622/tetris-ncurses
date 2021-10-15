#ifndef GUI_H
#define GUI_H

#define WIDTH 20
#define HEIGHT 40
#define XOFF 60
#define YOFF 2

#include <blocks.h>

void draw_gui();
void draw_block(Block b);
void draw_pixel(Pixel * p);
void draw_playfield(Playfield * pf);
Playfield * initialize_playfield(int width, int height);
#endif