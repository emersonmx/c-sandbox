#ifndef SDL2_TIMER_H
#define SDL2_TIMER_H

#include <stdint.h>

#include <SDL_timer.h>

#ifdef __cplusplus
extern "C" {
#endif

double timer_get_ticks_in_seconds(void)
{
    return SDL_GetPerformanceCounter() / (double)SDL_GetPerformanceFrequency();
}

uint32_t timer_get_ticks_in_milliseconds(void)
{
    return timer_get_ticks_in_seconds() * 1000;
}

#ifdef __cplusplus
}
#endif

#endif /* SDL2_TIMER_H */
