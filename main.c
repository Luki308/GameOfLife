#include "data.h"
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    world_t w = create_world(argv[1]);
    if(w != NULL)
    {
        print_world(w, stdout, true);
        //store_world(w, "nowy.txt");
        free_world(w);
    }

    return 0;
}
