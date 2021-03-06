#ifndef PONG_WALL_H
#define PONG_WALL_H

#include <cglm/vec3.h>

#include <sdl2/sdl2.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Wall {
    SDL_Color color;
    SDL_Rect rect;
    vec3 position;
} Wall;


SDL_Rect wall_rect(Wall* wall);
void wall_render(Wall* wall);

#ifdef __cplusplus
}
#endif

#endif /* PONG_WALL_H */
