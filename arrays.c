#include "arrays.h"
#include <stdio.h>
#include <stdbool.h>

bool check_if_char_in_array(char c, const char array[], int array_len)
{
    for(int i = 0; i < array_len; i++)
        if(c == array[i]) return true;
    return false;
}

bool check_if_int_in_array(int x, const int array[], int array_len)
{
    for(int i = 0; i < array_len; i++)
        if(x == array[i]) return true;
    return false;
}

void print_const_char_array(const char array[], int array_len, FILE *output)
{
    if(array_len < 1)
    {
        fprintf(stderr, "Array must by at least 1 char long to by written!");
        return;
    }

    fprintf(output, "[ %c", array[0]);
    for(int i = 1; i < array_len; i++)
        fprintf(output, ", %c", array[i]);
    fprintf(output, " ]\n");
}
