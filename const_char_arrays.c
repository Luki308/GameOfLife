#include "const_char_arrays.h"
#include <stdio.h>

char check_if_char_in_array(char c, const char array[], int array_len)
{
    for(int i = 0; i < array_len; i++)
        if(c == array[i]) return 1;
    return 0;
}

void print_const_char_array(const char array[], int array_len, FILE *output)
{
    if(array_len < 1)
    {
        fprintf(stderr, "Array must by at least 1 char long to by written!");
        return;
    }

    fprintf(output, "{ %c", array[0]);
    for(int i = 1; i < array_len; i++)
        fprintf(output, ", %c", array[i]);
    fprintf(output, " }\n");
}
