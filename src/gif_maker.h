# ifndef _GIF_MAKER_H_
# define _GIF_MAKER_H_

#include "gifenc.h"
#include "data.h"

int start_gif(char* name, int rows, int columns, int scale, int delay);
void paint_frame(world_t world);
void finish_gif();

# endif
