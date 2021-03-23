#include "data.h"
#include "game_of_life.h"
#include "gif_maker.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void programme_usage(char* argv)
{
    printf("Uzycie: %s\n"
        "-w [nazwa_swiata] - czytanie z podanego pliku\n"
        "-n [liczba_iteracji] - swiat zostanie wygenerowany do podanej generacji\n"
        "-g [nazwa_gifu] - kolejne generacje beda zapisane do podanego pliku gif\n"
        "-s [skala] - przeskalowanie wielkosci w pliku gif\n"
        "-d [opoznienie] - z jakim opoznieniem beda pokazywane generacje w pliku gif\n"
        , argv);
}

int main(int argc, char **argv)
{
    world_t w;
    int n=0;
    char* gif_name="";
    int scale=0;
    int delay=0;

    int opt;
    while ((opt = getopt(argc, argv, "w:n:g:s:d:"))!= -1)
    {
        switch (opt)
        {
        case 'w':
            w = create_world(optarg);
            break;
        case 'n':
            n = atoi(optarg);
            break;
        case 'g':
            gif_name = optarg;
            break;
        case 's':
            scale = atoi(optarg);
            break;
        case 'd':
            delay = atoi(optarg);
            break;
        default:
            programme_usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    if (argc == 1)
    {
        programme_usage(argv[0]);
        exit(EXIT_FAILURE);
    }
        
    //world_t w = create_world(argv[1]);
    //if (w == NULL)
      // free_world(w);
    /*int n = argc > 2 ? atoi(argv[2]) : 10;
    char* gif_name = argc > 3 ? argv[3] : "gif.gif";
    int scale = argc > 4 ? atoi(argv[4]) : 50 ;
    int delay = argc > 5 ? atoi(argv[5]) : 50 ;*/
    
    if (n == 0)
    {
        printf("%s: Wrong number of iterations. Changing to default number(10)\n", argv[0]);
        n = 10;
    }

    if ( strstr(gif_name, ".gif\0")==NULL)
    {
        printf("%s: Wrong gif filename. Changing to default name(gif.gif)\n", argv[0]);
        gif_name = "gif.gif";
    }

    if (scale==0)
    {
        printf("%s: Wrong scale. Changing to default number(50)\n", argv[0]);
        scale = 50;
    }
    if (delay==0)
    {
        printf("%s: Wrong delay. Changing to default number(50=0,5s)\n", argv[0]);
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