#ifndef PONG_MIDFIELD_H
#define PONG_MIDFIELD_H

#include <cglm/vec3.h>

#include <sdl2/sdl2.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MidField {
    SDL_Color color;
    SDL_Rect rect;
    vec3 position;
} MidField;


void midfield_render(MidField* midfield);

#ifdef __cplusplus
}
#endif

#endif /* PONG_MIDFIELD_H */
