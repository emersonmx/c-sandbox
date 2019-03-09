#ifndef CSB_SDL2_SDL2_TTF_H
#define CSB_SDL2_SDL2_TTF_H

#include <stdbool.h>

#include <SDL_ttf.h>

#ifdef __cplusplus
extern "C" {
#endif

bool sdl2_ttf_initialize(void);
void sdl2_ttf_finalize(void);

#ifdef __cplusplus
}
#endif

#endif /* CSB_SDL2_SDL2_TTF_H */
