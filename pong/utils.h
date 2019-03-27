#ifndef CSB_GAME_PONG_UTILS_H
#define CSB_GAME_PONG_UTILS_H

#include <stdbool.h>
#include <stddef.h>

#define COLOR_WHITE \
    (SDL_Color){255, 255, 255, SDL_ALPHA_OPAQUE}
#define COLOR_BLACK \
    (SDL_Color){0, 0, 0, SDL_ALPHA_OPAQUE}

#ifdef __cplusplus
extern "C" {
#endif

bool in_array(int needle, int* array, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* CSB_GAME_PONG_UTILS_H */