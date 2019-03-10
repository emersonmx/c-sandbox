#ifndef CSB_GAMES_PONG_BALL_H
#define CSB_GAMES_PONG_BALL_H

#include <cglm/vec3.h>

#include <sdl2/sdl2.h>

#include "render.h"

#define BALL_SPEED_STEP 5
#define BALL_DEFAULT_MIN_SPEED 100
#define BALL_DEFAULT_MAX_SPEED 1000

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Ball {
    SDL_Color color;
    SDL_Rect rect;
    vec3 position;
    vec3 velocity;
    double speed;
    double min_speed;
    double max_speed;
} Ball;


SDL_Rect ball_rect(Ball* ball);

void ball_reset(Ball* ball);
void ball_fixed_update(Ball* ball, double delta);
void ball_render(Ball* ball);

#ifdef __cplusplus
}
#endif

#endif /* CSB_GAMES_PONG_BALL_H */
