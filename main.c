#include "data.h"
#include "game_of_life.h"
#include "gif_maker.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

int main(int argc, char **argv)
{
    world_t w = create_world(argv[1]);
    int n = argc > 2 ? atoi(argv[2]) : 10;
    char* gif_name = argc > 3 ? argv[3] : "gif.gif";
    int scale = argc > 4 ? atoi(argv[4]) : 50 ;
    int delay = argc > 5 ? atoi(argv[5]) : 25 ;
    
    if (n == 0)
    {
        printf("%s: Wrong number of iterations. Changing to default number\n", argv[0]);
        n = 10;
    }

    if ( strstr(gif_name, ".gif\0")==NULL)
    {
        printf("%s: Wrong gif filename. Changing to default name\n", argv[0]);
        gif_name = "gif.gif";
    }

    if (scale==0)
    {
        printf("%s: Wrong scale. Changing to default number\n", argv[0]);
        scale = 50;
    }
    if (delay==0)
    {
        printf("%s: Wrong delay. Changing to default number\n", argv[0]);
        delay = 25;
    }

    start_gif(gif_name, w->rows, w->columns, scale, delay);
    paint_frame(w);          //adding first frame to gif
    
    usage();
    int i=0;
    while (i < n)
    {
        char* temp;
        int ni;
        int j;
        printf("%i\n", i);
        printf("Operacja do wykonania:");
        /*temp = getc(stdin);
        temp = getc(stdin);*/
        if(scanf("%s", temp) != 1)
        {
            fprintf(stderr, "%s: Cannot read character\n", argv[0]);
        }

        if (strlen(temp) != 1)
        {
            fprintf(stderr, "\n%s: Wrong argument.\n Please use one from below\n", argv[0]);
            usage();
            continue;
        }
        switch (temp[0])
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
            j = i;
            while (i < j + ni && i<n)
            {
                update(w);
                paint_frame(w);
                i++;
            }
            break;
        case 'n':
            update(w);
            paint_frame(w);
            i++;
            break;
        case 'd':
            print_world(w, stdout, 1);
            break;
        case 'h':
            usage();
           break;
        default:
            usage();
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