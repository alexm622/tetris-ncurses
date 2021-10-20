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

bool gameOverCheck(Block b);

int checkPlayfield(Playfield *p);

void removeRow(Playfield *p, int row);
void moveRowsDown(Playfield *p, int lastrow);

int inc_score(int num_rows, int level);
#endif
