# ifndef _DATA_H_
# define _DATA_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct w {
    int rows;
    int columns;
    char **cells; 
} *world_t;

world_t alloc_world(int rows, int columns);
void free_world(world_t world);
world_t create_world(char *filename);
void print_world(world_t world, FILE *output, bool size_info);
void store_world(world_t world, char *filename);

# endif
