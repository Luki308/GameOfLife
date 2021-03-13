#include "data.h"
#include "game_of_life.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    world_t w = create_world(argv[1]);
    printf("Swiat na poczatku\n:");
    print_world(w, stdout, 1);
    printf("\nIle generacji przeprowadzic\n:");
    int n;
    scanf("%d",&n);
    for (int i = 0;i < n;i++)
    {
        update(w);
        store_world(w, "nowy.txt");
    }
    print_world(w, stdout, 1);
    if(w != NULL)
        free_world(w);


    printf("Game of Life Simulator\n");
    return 0;
}
