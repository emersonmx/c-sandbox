#ifndef PONG_SHADE_H
#define PONG_SHADE_H

#include <cglm/vec3.h>

#include <sdl2/sdl2.h>

#include "render.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Shade {
    SDL_Color color;
    SDL_Rect rect;
    vec3 position;
    bool visibility;
} Shade;

void shade_init(Shade* shade);
void shade_show(Shade* shade);
void shade_hide(Shade* shade);
void shade_update(Shade* shade, double delta);
void shade_render(Shade* shade);

#ifdef __cplusplus
}
#endif

#endif /* PONG_SHADE_H */
