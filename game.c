#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#define sac 2
#define bbc 1
static const char stay_alive_condition[sac] = { '2', '3' };
static const char be_born_condition[bbc] = { '3' };

void update(world_t world) //iteration
{
    for (int i = 0; i < world->rows; i++)
    {
        for (int j = 0; j < world->columns; j++)
        {
            int alive = alive_neighbours(i, j, world);
            world->cells[i][j] = apply_rules(alive, i,j, world);
        }
    }
    update_world(world);
}


int alive_neighbours(int row, int column, world_t world) //counting neighbours
{
    int alive=0;
    for (int i = row-1; i <=row+1 ; i++)
    {
        for (int j = column-1; j <=column+1; j++)
        {
            if (i >= 0 && i<world->rows && j >= 0 && j < world->columns && (i!=row || j!=column)) //checking if neighbour is in world's boundaries and if it's cell itself
            {
                if (world->cells[i][j] == '1' || world->cells[i][j]=='3')
                    alive++;
            }
        }
    }
    return alive;
}

char apply_rules(int alive, int r, int c, world_t world) //changing cells
{
            if (world->cells[r][c] == '0')
                for (int i = 0; i < bbc; i++)
                    if ((alive+'0') == be_born_condition[i])   return '2';

            if (world->cells[r][c] == '1')
            {
                for (int i = 0; i < sac; i++)
                {
                    if ((alive+'0') == stay_alive_condition[i])
                    {
                        return '1';
                    }
                }
                return '3';
            }
                  
}

void update_world(world_t world)  // changing 2->1 3->0
{
    for (int i = 0; i < world->rows; i++)
    {
        for (int j = 0; j < world->columns; j++)
        {
            if (world->cells[i][j] == '2')
            {
                world->cells[i][j] = '1';
            }
            if (world->cells[i][j] == '3')
            {
                world->cells[i][j] = '0';
            }
        }
    }
}