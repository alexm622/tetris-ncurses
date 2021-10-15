#ifndef GAME_H
#define GAME_H
#include <stdbool.h>
#include <blocks.h>
bool updateBlock(Block b, int dy, int dx);
bool shiftBlockX(Block b, int dx);
bool shiftBlockY(Block b, int dy);

#endif