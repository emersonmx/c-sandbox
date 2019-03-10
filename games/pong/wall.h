#ifndef CSB_GAMES_PONG_WALL_H
#define CSB_GAMES_PONG_WALL_H

#include <cglm/vec3.h>

#include <sdl2/sdl2.h>

#include "render.h"

#define TOP_WALL 0
#define BOTTOM_WALL 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Wall {
    SDL_Color color;
    SDL_Rect rect;
    vec3 position;
} Wall;

#ifdef __cplusplus
}
#endif

void wall_render(Wall* wall);

#endif /* CSB_GAMES_PONG_WALL_H */
