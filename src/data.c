#include "data.h"
#include "arrays.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 256 // max length of input word (only first letter matters)

static const char cell_states[2] = { '0', '1' };
static const int number_of_cell_states = sizeof cell_states / sizeof cell_states[0];


void free_world(world_t world) // cleans memory after world usage
{
    if(world != NULL)
    {
        if(world->cells != NULL)
        {
            for(int i = 0; i < world->rows; i++)
                if(world->cells[i] != NULL)
                    free(world->cells[i]);
            free(world->cells);
        }
        free(world);
    }
}

world_t alloc_world(int rows, int columns) // allocs memory for world
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
        free_world(world);
        return NULL;
    }

    for(int i = 0; i < rows; i++)
    {
        world->cells[i] = malloc(columns * sizeof **world->cells);
        if(world->cells[i] == NULL)
        {
            fprintf(stderr, "Cannot alloc enough memory for all cells! Problem in row (from 0): %d\n", i);
            free_world(world);
            return NULL;
        }
    }

    return world;
}

world_t create_world(char *filename) // reads world from file
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

    char buffer[BUFFER_SIZE];
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

            if(!check_if_char_in_array(world->cells[i][j], cell_states, number_of_cell_states))
            {
                fprintf(stderr, "Wrong data format in: %s! Illegal cell's state!\n", filename);
                fprintf(stderr, "Row: %d   Column: %d\n", i, j);
                fprintf(stderr, "There is no '%c' in: ", world->cells[i][j]);
                print_const_char_array(cell_states, number_of_cell_states, stderr);
                free_world(world);
                fclose(in);
                return NULL;
            }
        }
    fclose(in);    
    return world;
}

void print_world(world_t world, FILE *output, bool size_info) // writes world on given output
{
    if(world == NULL)
    {
        fprintf(stderr, "Cannot print world which is NULL!\n");
        return;
    }

    if(size_info)
        fprintf(output, "%d %d\n", world->rows, world->columns);

    for(int i = 0; i < world->rows; i++)
    {
        for(int j = 0; j < world->columns; j++)
            fprintf(output, "%c ", world->cells[i][j]);
        fprintf(output, "\n");
    }            
    fprintf(output, "\n");
}

void store_world(world_t world, char *filename) // makes input file from current world
{
    FILE *out = fopen(filename, "w");
    if(out == NULL)
    {
        fprintf(stderr, "Cannot write to file: %s!\n", filename);
        return;
    }
    print_world(world, out, 1);
}

char* get_filename(char* input_file)
{
    char* filename;
    if ((filename = strrchr(input_file, '/')) != NULL)
        filename++;
    else if ((filename = strrchr(input_file, '\\')) != NULL)
        filename++;
    else filename = input_file;

    return filename;
}

void save_to_file(char* save_file, char* filename, world_t world, int i)
{
    memset(save_file, '\0', strlen(save_file));
    if (strstr(filename, ".txt\0") != NULL)
        strncpy(save_file, filename, strlen(filename) - 4);
    else
        strncpy(save_file, filename, strlen(filename));
    char suffix[10];
    snprintf(suffix, 10, "%d.txt", i);
    strcat(save_file, suffix);
    FILE* out = fopen(save_file, "w");
    print_world(world, out, true);
    printf("Zapisano do pliku: %s\n", save_file);
    fclose(out);
}