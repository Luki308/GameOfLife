#include "game_of_life.h"
#include "const_char_arrays.h"
#include <stdio.h>
#include <stdlib.h>

/*
    Cell states and temporary states:
    0 - dead
    1 - alive
    2 - being born
    3 - dieing
*/

// numbers in these conditions are represented by chars for lower memory usage and functions compatibility
const char stay_alive_condition[2] = { '2', '3' };
const char be_born_condition[1] = { '3' };
const int size_of_stay_alive_array = sizeof stay_alive_condition / sizeof stay_alive_condition[0];
const int size_of_be_born_array = sizeof be_born_condition / sizeof be_born_condition[0];


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

int alive_neighbours(int row, int column, world_t world) //counting neighbours
{
    int alive = 0;
    for (int i = row-1; i <= row+1; i++)
    {
        for (int j = column-1; j <= column+1; j++)
        {
            if (i >= 0 && i < world->rows && j >= 0 && j < world->columns && (i != row || j != column)) //checking if neighbour is in world's boundaries and if it's cell itself
            {
                if (world->cells[i][j] == '1' || world->cells[i][j] == '3')
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
        if (check_if_char_in_array(alive_neighbours+'0', be_born_condition , size_of_be_born_array))
            return '2';
        else 
            return '0';
    }
    else if (cell == '1')
    {
        if (check_if_char_in_array(alive_neighbours+'0', stay_alive_condition, size_of_stay_alive_array))
            return '1';
        else
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
