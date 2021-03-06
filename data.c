#include "data.h"
#include "const_char_arrays.h"
#include <stdio.h>
#include <stdlib.h>

static const char cell_states[2] = { '0', '1' };
static const int cs = sizeof cell_states / sizeof cell_states[0];

world_t alloc_world(int rows, int columns)
{
    world_t world = malloc(sizeof(*world));
    if(world == NULL)
    {
        fprintf(stderr, "Cannot alloc enough memory for world variable!\n");
        return NULL;
    }

    world->cells = malloc(rows * sizeof *world->cells);
    if(world->cells == NULL)
    {
        fprintf(stderr, "Cannot alloc enough memory for cells' pointers!\n");
        free(world);
        return NULL;
    }

    for(int i = 0; i < rows; i++)
    {
        world->cells[i] = malloc(columns * sizeof **world->cells);
        if(world->cells[i] == NULL)
        {
            fprintf(stderr, "Cannot alloc enough memory for all cells! Problem in row (from 0): %d\n", i);
            for(int j = 0; j < i; j++)
                free(world->cells[j]);
            free(world->cells);
            free(world);
            return NULL;
        }
    }

    return world;
}

void free_world(world_t world)
{
    for(int i = 0; i < world->rows; i++)
        free(world->cells[i]);
    free(world->cells);
    free(world);
}

world_t create_world(char *filename)
{
    FILE *in = fopen(filename, "r");
    if(in == NULL)
    {
        fprintf(stderr, "Cannot read file: %s!\n", filename);
        return NULL;
    }

    int r;
    int c;
    if(fscanf(in, "%d %d", &r, &c) != 2)
    {
        fprintf(stderr, "Wrong data format in: %s! Need integer number of rows and columns!\n", filename);
        fclose(in);
        return NULL;
    }
    if(r < 1 || c < 1)
    {
        fprintf(stderr, "Making less rows or columns than 1 isn't allowed!\n Rows: %d\n Columns: %d\n", r, c);
        fclose(in);
        return NULL;
    }

    world_t world = alloc_world(r, c);
    if(world == NULL)
    {
        fprintf(stderr, "World cannot be allocated!\n");
        fclose(in);
        return NULL;
    }

    world->rows = r;
    world->columns = c;

    char buffer[256];
    for(int i = 0; i < world->rows; i++)
        for(int j = 0; j < world->columns; j++)
        {
            if(fscanf(in, "%s", buffer) != 1)
            {
                fprintf(stderr, "Wrong data format in: %s! Need more cells!\n", filename);
                free_world(world);
                fclose(in);
                return NULL;
            }

            world->cells[i][j] = buffer[0];

            if(!check_if_char_in_array(world->cells[i][j], cell_states, cs))
            {
                fprintf(stderr, "Wrong data format in: %s! Illegal cell's state!\n", filename);
                fprintf(stderr, "Row: %d   Column: %d\n", i, j);
                fprintf(stderr, "There is no '%c' in: ", world->cells[i][j]);
                print_const_char_array(cell_states, cs, stderr);
                free_world(world);
                fclose(in);
                return NULL;
            }
        }
    fclose(in);    
    return world;
}

void print_world(world_t world, FILE *output, char all_info)
{
    if(world == NULL)
    {
        fprintf(stderr, "World is NULL!\n");
        return;
    }

    if(all_info)
        fprintf(output, "%d %d\n", world->rows, world->columns);

    for(int i = 0; i < world->rows; i++)
    {
        for(int j = 0; j < world->columns; j++)
            fprintf(output, "%c ", world->cells[i][j]);
        fprintf(output, "\n");
    }            
    fprintf(output, "\n");
}

void store_world(world_t world, char *filename)
{
    FILE *out = fopen(filename, "w");
    if(out == NULL)
    {
        fprintf(stderr, "Cannot write to file: %s!\n", filename);
        return;
    }
    print_world(world, out, 1);
}
