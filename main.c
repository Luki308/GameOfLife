#include "data.h"
#include "game_of_life.h"
#include "gif_maker.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
    world_t w = create_world(argv[1]);
    int n = argc > 2 ? atoi(argv[2]) : 50;
    char* gif_name = argc > 3 ? argv[3] : "gif.gif";

    int scale;
    int delay;

    printf("Ilukrotnie przeskalowac plik wynikowy gif:\n");
    scanf("%d", &scale);
    printf("Ile czasu ma minac pomiedzy kolejnymi iteracjami w pliku gif [ms]:\n");
    scanf("%d", &delay);
    start_gif(gif_name, w->rows, w->columns, scale, delay);
    paint_frame(w);          //adding first frame to gif
    

    usage();
    for (int i = 0;i < n;i++)
    {
        char temp;
        int ni;
        int j = i;
        printf("%i\n", i);
        printf("Operacja do wykonania:");
        temp = getc(stdin);
        temp = getc(stdin);
        switch (temp)
        {
        case 'a':
            while (i < n)
            {
                update(w);
                paint_frame(w);
                i++;
            }
            break;
        case 'f':
            printf("Ile iteracji do przodu:\n");
            scanf("%d", &ni);
            while (i <= j + ni && i<n)
            {
                update(w);
                paint_frame(w);
                i++;
            }
            break;
        case 'n':
            update(w);
            paint_frame(w);
            break;
        case 'd':
            print_world(w, stdout, 1);
            i--;
            break;
        case 'h':
            usage();
            i--;
           break;
        }
    }
    finish_gif();
    print_world(w, stdout, 1);
    if(w != NULL)
        free_world(w);

    return 0;
}


void usage()
{
    printf("a - przejscie do koncowej wersji swiata\n"
           "f - wykonanie x iteracji\n"
           "n - wykonanie kolejnej iteracji\n"
           "d - wyswietlanie swiata\n"
           "h - pokazanie pomocy\n");
}