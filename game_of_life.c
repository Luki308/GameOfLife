#include "game_of_life.h"
#include "arrays.h"
#include <stdio.h>
#include <stdlib.h>

/*
    Cell states and temporary states:
    0 - dead
    1 - alive
    2 - dying
    3 - being born
*/

// numbers in these conditions are represented by chars for lower memory usage and functions compatibility
static const int stay_alive_condition[2] = { 2, 3 };
static const int be_born_condition[1] = { 3 };
static const int size_of_stay_alive_array = sizeof stay_alive_condition / sizeof stay_alive_condition[0];
static const int size_of_be_born_array = sizeof be_born_condition / sizeof be_born_condition[0];


void update(world_t world) //iteration
{
    for (int i = 0; i < world->rows; i++)
    {
        for (int j = 0; j < world->columns; j++)
        {
            int alive = alive_neighbours(i, j, world);
            world->cells[i][j] = apply_rules(alive, world->cells[i][j]);
        }
    }
    update_world(world);
}

//  beyond the border neighbours are counted as if world was "round"
int Magellan(int x, int max_len) //changing location of examined neighbours in order to recognize neighbours on the opposite border of the world
{
    if(x == -1) return max_len-1;
    else return x % max_len;
}

int alive_neighbours(int row, int column, world_t world) //counting neighbours
{
    int alive = 0;
    for (int i = row-1; i <= row+1; i++)
    {
        for (int j = column-1; j <= column+1; j++)
        {
            if (i != row || j != column) //checking if it's not the cell itself
            {
                int x = Magellan(i, world->rows);
                int y = Magellan(j, world->columns);
                if (world->cells[x][y] == '1' || world->cells[x][y] == '2')
                    alive++;
            }
        }
    }
    return alive;
}

char apply_rules(int alive_neighbours, char cell) //changing cells
{
    if (cell == '0')
    {
        if (check_if_int_in_array(alive_neighbours, be_born_condition , size_of_be_born_array))
            return '3';
        else 
            return '0';
    }
    else if (cell == '1')
    {
        if (check_if_int_in_array(alive_neighbours, stay_alive_condition, size_of_stay_alive_array))
            return '1';
        else
            return '2';           
    }
}

void update_world(world_t world)  // changing 3->1 2->0
{
    for (int i = 0; i < world->rows; i++)
    {
        for (int j = 0; j < world->columns; j++)
        {
            if (world->cells[i][j] == '2' || world->cells[i][j] == '3')
                world->cells[i][j] -= 2;
        }
    }
}
