#ifndef PONG_SCORE_H
#define PONG_SCORE_H

#include <cglm/vec3.h>

#include <sdl2/sdl2.h>
#include <sdl2/sdl2_ttf.h>

#include "render.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Score Score;
struct Score {
    SDL_Color color;
    SDL_Rect rect;
    vec3 position;
    vec3 origin;
    int value;

    SDL_Texture* texture;
};


void score_update_score(Score* score, int value);
void score_reset(Score* score);
void score_render(Score* score);

#ifdef __cplusplus
}
#endif

#endif /* PONG_SCORE_H */
