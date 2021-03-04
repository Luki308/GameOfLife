#include <stdio.h>
#include <stdlib.h>


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
        free(world);
        fprintf(stderr, "Cannot alloc enough memory for cells' pointers!\n");
        return NULL;
    }

    for(int i = 0; i < rows; i++)
    {
        world->cells[i] = malloc(columns * sizeof **world->cells);
        if(world->cells[i] == NULL)
        {
            for(int j = 0; j < i; j++)
                free(world->cells[j]);
            free(world->cells);
            free(world);
            fprintf(stderr, "Cannot alloc enough memory for all cells! Problem in row (from 0): %d\n", i);
            return NULL;
        }
    }

    return world;
}

void free_world(world_t world)
{
    for(int j = 0; j < world->columns; j++)
        free(world->cells[j]);
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
        fclose(in);
        fprintf(stderr, "Wrong data format in: %s! Need integer number of rows and columns!\n", filename);
        return NULL;
    }
    if(r < 1 || c < 1)
    {
        fclose(in);
        fprintf(stderr, "Making less rows or columns than 1 isn't allowed!\n Rows: %d\n Columns: %d\n", r, c);
        return NULL;
    }

    world_t world = alloc_world(r, c);
    if(world == NULL)
    {
        fclose(in);
        fprintf(stderr, "World cannot be allocated!\n");
        return NULL;
    }

    world->rows = r;
    world->columns = c;

    for(int i = 0; i < world->rows; i++)
        for(int j = 0; j < world->columns; j++)
            if(fscanf(in, "%c", &world->cells[i][j]) != 1)
            {
                free_world(world);
                fclose(in);
                fprintf(stderr, "Wrong data format in: %s! Need more cells!\n", filename);
                return NULL;
            }

    fclose(in);    
    return world;
}

void store_world(world_t world)
{
    printf("It's a placeholder\n");
}
