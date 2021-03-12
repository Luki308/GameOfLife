# ifndef _GAME_OF_LIFE_H_
# define _GAME_OF_LIFE_H_

#include "data.h"

void update(world_t world);
int alive_neighbours(int row, int column, world_t world);
char apply_rules(int alive_neighbours, char cell);
void update_world(world_t world);

# endif
