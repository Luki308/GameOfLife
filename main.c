#include "data.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    world_t w = create_world(argv[1]);
    print_world(w, 1);
    if(w != NULL)
        free_world(w);


    printf("Game of Life Simulator\n");
    return 0;
}
