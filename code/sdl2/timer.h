#ifndef CSB_SDL2_TIMER_H
#define CSB_SDL2_TIMER_H

#include <stdint.h>

#include <SDL_timer.h>

#ifdef __cplusplus
extern "C" {
#endif

double timer_get_ticks_in_seconds(void);
uint32_t timer_get_ticks_in_milliseconds(void);

#ifdef __cplusplus
}
#endif

#endif /* CSB_SDL2_TIMER_H */
