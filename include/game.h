#ifndef GAME_H
#define GAME_H
#include <stdbool.h>
#include <blocks.h>
bool updateBlock(Block b, Playfield* p, int dy, int dx, bool drop);
bool shiftBlockX(Block b, int dx);
bool shiftBlockY(Block b, int dy);

void addToPlayfield(Block *b, Playfield* p);

bool playfieldCollisionCheck(Block b, Playfield* p, int dx, int dy, bool drop);
bool playfieldCollisionCheckX(Block b, Playfield* p, int dx);
bool playfieldCollisionCheckY(Block b, Playfield* p, int dy);

#endif