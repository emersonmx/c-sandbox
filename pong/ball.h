#ifndef PONG_BALL_H
#define PONG_BALL_H

#include <cglm/vec3.h>

#include <sdl2/sdl2.h>

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
    Uint32 play_delay;
} Ball;


SDL_Rect ball_rect(Ball* ball);

void ball_reset(Ball* ball);
void ball_play(Ball* ball);
void ball_play_with_delay(Ball* ball);
void ball_fixed_update(Ball* ball, double delta);
void ball_render(Ball* ball);

#ifdef __cplusplus
}
#endif

#endif /* PONG_BALL_H */
