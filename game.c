#include <stdio.h>
#include "game.h"
const int sac = 2;
const int bbc = 1;
static const char stay_alive_condition[sac] = { 2, 3 };
static const char be_born_condition[bbc] = { 3 };

void update(world_t world) //iteration
{
    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = column - 1; j < column + 1; j++)
        {
            int alive = alive_neighbours(i, j, world);
            world->cells[i][j] = apply_rules(alive, world->cells[i][j], world);
        }
    }
    update_world();
}


int alive_neighbours(int row, int column, world_t world) //counting neighbours
{
    int alive=0;
    for (int i = row-1; i <=row+1 ; i++)
    {
        for (int j = column-1; j <column+1; j++)
        {
            if (i >= 0 && i<row && j >= 0 && j < column && i!=j) //checking if neighbour is in world's boundaries and if it's cell itself
            {
                if (world->cells[i][j] == 1)
                    alive++;
            }
        }
    }
    return alive;
}

char apply_rules(int alive, char cell, world_t world) //changing cells
{
            if (cell == 0)
                for (int i = 0; i < bbc; i++)
                    if (alive == be_born_condtion[i])   return 2;

            if (cell == 1)
            {
                for (int i = 0; i < sac; i++)
                {
                    if (alive == stay_alive_condition[i])
                    {
                        return 1;
                    }
                }
                return 3;
            }
                  
}

void update_world(world_t world)  // changing 2->1 3->0
{
    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = column - 1; j < column + 1; j++)
        {
            if (world->cells[i][j] == 2)
            {
                world->cells[i][j] = 1;
            }
            if (world->cells[i][j] == 3)
            {
                world->cells[i][j] = 0;
            }
        }
    }
}