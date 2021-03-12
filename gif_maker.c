#include "gifenc.h"
#include "data.h"

static ge_GIF *gif;
static int scale;
static int delay;

void start_gif(char* name, int rows, int columns, int given_scale, int given_delay)
{
    scale = given_scale;
    delay = given_delay;
    gif = ge_new_gif(
        name,   // name of output gif file
        scale * rows, scale * columns,  // scaled up dimensions
        (uint8_t []) {  // palette
            0xFF, 0xFF, 0xFF,   // 0 -> white
            0x00, 0x00, 0x00,   // 1 -> black
        },
        1,  // palette depth == log2(x)  (x - number of colors)
        0   // infinite loop
    );
}

void paint_frame(world_t world)
{
    for(int r = 0; r < scale * world->rows; r++)
        for(int c = 0; c < scale * world->columns; c++)
            gif->frame[r * world->rows + c] = world->cells[r/scale][c/scale];
    ge_add_frame(gif, delay);
}

void finish_gif()
{
    ge_close_gif(gif);
}
