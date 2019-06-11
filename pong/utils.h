#ifndef PONG_UTILS_H
#define PONG_UTILS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define COLOR_WHITE \
    (SDL_Color){255, 255, 255, SDL_ALPHA_OPAQUE}
#define COLOR_BLACK \
    (SDL_Color){0, 0, 0, SDL_ALPHA_OPAQUE}

#ifdef __cplusplus
extern "C" {
#endif

bool in_array(int32_t needle, int32_t* array, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* PONG_UTILS_H */
