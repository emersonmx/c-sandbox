#include "sdl2_ttf.h"

bool sdl2_ttf_initialize(void)
{
    return TTF_Init() == 0;
}

void sdl2_ttf_finalize(void)
{
    TTF_Quit();
}
