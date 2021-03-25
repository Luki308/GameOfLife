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
    printf("\nUzycie: %s\n"
        "-n [liczba_iteracji] - swiat zostanie wygenerowany do podanej generacji\n"
        "-w [plik_wejsciowy] - czytanie swiata z podanego pliku\n"
        "-g [nazwa_gifu] - kolejne generacje beda zapisane do podanego pliku gif (nazwa zakonczona na \".gif\")\n"
        "-s [skala] - przeskalowanie wielkosci w pliku gif\n"
        "-d [opoznienie] - z jakim opoznieniem beda pokazywane generacje w pliku gif (w setnych sekundy)\n\n"
        , argv);
}

void usage()
{
    printf("\na [automatic] - przejscie do koncowej wersji swiata\n"
        "f [fast forward] - wykonanie x iteracji\n"
        "n [next] - wykonanie kolejnej iteracji\n"
        "d [display] - wyswietlanie swiata\n"
        "s [save] - zapisanie biezacej iteracji jako plik wejsciowy\n"
        "h [help] - pokazanie pomocy\n\n");
}

void generate(world_t world, int *i)
{
    update(world);
    paint_frame(world);
    (*i)++;
} 

#define BUFFER_SIZE 256 // max length of input word (only first letter matters)

// default values chosen when not specified
#define N 20
#define INPUT_FILE "examples/swarm.txt"
#define GIF_NAME "generated_gif.gif"
#define SCALE 50
#define DELAY 25


int main(int argc, char **argv)
{
    world_t w = NULL;
    int n = N;
    char* gif_name = GIF_NAME;
    char* input_file = INPUT_FILE;
    int scale = SCALE;
    int delay = DELAY;

    int opt;
    while ((opt = getopt(argc, argv, "n:w:g:s:d:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            n = atoi(optarg);
            if (n <= 0)
            {
                printf("%s: %d is wrong number of iterations. Changing to default number(%d)\n", argv[0], n, N);
                n = N;
            }
            break;
        case 'w':
            input_file = optarg;
            break;
        case 'g':
            gif_name = optarg;          
            if (strstr(gif_name, ".gif\0") == NULL || strlen(gif_name) <= 4)
            {
                printf("%s: %s is wrong gif filename. Changing to default name(%s)\n", argv[0], gif_name, GIF_NAME);
                gif_name = GIF_NAME;
            }
            break;
        case 's':
            scale = atoi(optarg);
            if (scale <= 0)
            {
                printf("%s: %d is wrong scale. Changing to default number(%d)\n", argv[0], scale, SCALE);
                scale = SCALE;
            }
            break;
        case 'd':
            delay = atoi(optarg);
            if (delay < 6)
            {
                printf("%s: %d is wrong delay. Changing to default number(%d=%ds)\n", argv[0], delay, DELAY, DELAY/100);
                delay = DELAY;
            }
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
    

    w = create_world(input_file);
    if(w == NULL)
    {
        printf("World is NULL!\n");
        return EXIT_FAILURE;
    }
    else   // if world has been created successfully
    {
        if(start_gif(gif_name, w->rows, w->columns, scale, delay) != 0)
        {
            printf("Gif has not been initialized properly!\n");
            return EXIT_FAILURE;
        }
        else    // if gif has been initialized successfully
        { 
            paint_frame(w);     //adding first frame to gif
            usage();

            // some operations related to saving to input file
            char *filename;
            if((filename = strrchr(input_file, '/')) != NULL)
                filename++;
            else if((filename = strrchr(input_file, '\\')) != NULL)
                filename++;
            else filename = input_file;
            char *save_file = malloc(sizeof filename + 5);    // name of generated input file (+5 to give space for number of generation)

            int i = 0;
            while (i < n)
            {
                char command[BUFFER_SIZE];

                printf("Operacja do wykonania: \n");
                if(scanf("%s", command) != 1)
                {
                    fprintf(stderr, "%s: Cannot read character\n", argv[0]);
                }
                if(strlen(command) > 1)
                {
                        printf("\nNie ma wieloznakowych polecen!\n");
                        continue;
                }

                switch (command[0])
                {
                    case 'a':
                        while (i < n)
                        {
                            generate(w, &i);
                        }
                        break;
                    case 'f':
                        printf("Ile iteracji do przodu: \n");
                        int j;
                        scanf("%d", &j);
                        j += i;
                        while (i < j && i < n)
                        {
                            generate(w, &i);
                        }
                        break;
                    case 'n':
                        generate(w, &i);
                        break;
                    case 'd':
                        print_world(w, stdout, false);
                        break;
                    case 's':
                        memset(save_file,'\0',strlen(save_file));
                        strncpy(save_file, filename, strlen(filename) - strlen(strstr(filename, ".txt\0")));
                        char suffix[10];
                        snprintf(suffix, 10, "%d.txt", i);
                        strcat(save_file, suffix);
                        FILE *out = fopen(save_file,"w");
                        print_world(w, out, true);
                        printf("Zapisano do pliku: %s\n",save_file);
                        fclose(out);
                        break;
                    case 'h':
                        usage();
                        break;
                    default:
                        printf("\nNieznane polecenie!\nProsze uzywac tych widocznych ponizej:\n");
                        usage();
                        break;
                }
            }
            free(save_file);
            finish_gif();
            printf("\nPlik gif \"%s\" zostal utworzony prawidlowo!\n\n", gif_name);
        }
        free_world(w);    
        return EXIT_SUCCESS;
    }
}
