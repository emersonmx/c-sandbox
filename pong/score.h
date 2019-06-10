#ifndef PONG_SCORE_H
#define PONG_SCORE_H

#include <cglm/vec3.h>

#include <sdl2/sdl2.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Score {
    SDL_Color color;
    SDL_Rect rect;
    vec3 position;
    vec3 origin;
    uint32_t value;

    SDL_Texture* texture;
} Score;


void score_update_score(Score* score, uint32_t value);
void score_reset(Score* score);
void score_render(Score* score);

#ifdef __cplusplus
}
#endif

#endif /* PONG_SCORE_H */
