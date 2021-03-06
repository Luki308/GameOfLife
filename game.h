#include <stdio.h>
#include "data.h"


void update(world_t world);
int alive_neighbours(int row, int column, world_t);
char apply_rules(int alive, int r, int c, world_t world);
void update_world(world_t world);