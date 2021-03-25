# ifndef _DATA_H_
# define _DATA_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct w {
    int rows;
    int columns;
    char **cells; 
} *world_t;

void free_world(world_t world);
world_t alloc_world(int rows, int columns);
world_t create_world(char *filename);
void print_world(world_t world, FILE *output, bool size_info);
void store_world(world_t world, char *filename);
char* get_filename(char* input_file);
void save_to_file(char* save_file, char* filename, world_t world, int i);

# endif
