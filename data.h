# ifndef _DATA_H_
# define _DATA_H_

typedef struct w {
    int rows;
    int columns;
    char **cells; 
} *world_t;

world_t alloc_world(int rows, int columns);
void free_world(world_t world);
world_t create_world(char *filename);
void store_world(world_t world);
void print_world(world_t world, char all_info);

# endif
