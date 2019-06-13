#include "timer.h"

double timer_get_ticks_in_seconds(void)
{
    return SDL_GetPerformanceCounter() / (double)SDL_GetPerformanceFrequency();
}

uint32_t timer_get_ticks_in_milliseconds(void)
{
    return timer_get_ticks_in_seconds() * 1000;
}

