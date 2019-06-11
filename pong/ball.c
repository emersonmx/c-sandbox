#include "ball.h"

#include <utils/random.h>

#include "app.h"
#include "render.h"
#include "object.h"
#include "events.h"

static int8_t ball_out_of_bounds_tid = -1;

static void change_direction(Ball* ball, vec3 anchor);
static void increate_min_speed(Ball* ball, double delta);
static void decrease_speed_defaut(Ball* ball, double delta);
static void decrease_speed(Ball* ball, double slowdown);

static Uint32 ball_out_of_bounds(Uint32 interval, void* param)
{
    SDL_Event event;
    SDL_zero(event);
    event.type = events_get_id();
    event.user.code = BALL_OUT_OF_BOUNDS_EVENT;
    event.user.data1 = param;
    SDL_PushEvent(&event);

    ball_out_of_bounds_tid = -1;

    return 0;
}

static Uint32 ball_delay_timeout(Uint32 interval, void* param)
{
    SDL_Event event;
    SDL_zero(event);
    event.type = events_get_id();
    event.user.code = PLAY_BALL_EVENT;
    SDL_PushEvent(&event);
    return 0;
}

SDL_Rect ball_rect(Ball* ball)
{
    return object_rect(ball);
}

void ball_reset(Ball* ball)
{
    App* app = app_instance();

    glm_vec3_copy((vec3){
        app->settings.window.width / 2.0f,
        app->settings.window.height / 2.0f,
        0
    }, ball->position);
    ball->speed = BALL_DEFAULT_MIN_SPEED;
    ball->min_speed = BALL_DEFAULT_MIN_SPEED;
    ball->max_speed = BALL_DEFAULT_MAX_SPEED;
    glm_vec3_copy(GLM_VEC3_ZERO, ball->velocity);
}

void ball_play(Ball* ball)
{
    glm_vec3_copy(GLM_XUP, ball->velocity);
    glm_vec3_rotate(
        ball->velocity,
        random_number(-GLM_PI_4, GLM_PI_4),
        GLM_ZUP
    );

    ball->velocity[0] *= random_int(0, 1) == 0 ? -1 : 1;
}

void ball_play_with_delay(Ball* ball)
{
    SDL_AddTimer(ball->play_delay, ball_delay_timeout, NULL);
}

void ball_fixed_update(Ball* ball, double delta)
{
    vec3 tmp;
    App* app = app_instance();
    Player* p1 = &app->game.player1;
    Player* p2 = &app->game.player2;
    SDL_Rect br = ball_rect(ball);
    SDL_Rect p1r = player_rect(p1);
    SDL_Rect p2r = player_rect(p2);
    SDL_Rect twr = wall_rect(&app->game.top_wall);
    SDL_Rect bwr = wall_rect(&app->game.bottom_wall);
    SDL_Rect par = app->game.play_area;

    if (SDL_HasIntersection(&br, &p1r)) {
        if (p1->is_strong_hit) {
            ball->speed = fmax(p1->speed*p1->hit_force, ball->speed);
        } else {
            decrease_speed(ball, ball->speed * p2->damp_force);
        }

        glm_vec3_zero(tmp);
        player_anchor(p1, tmp);
        change_direction(ball, tmp);
    }

    if (SDL_HasIntersection(&br, &p2r)) {
        if (p2->is_strong_hit) {
            ball->speed = fmax(p2->speed*p1->hit_force, ball->speed);
        } else {
            decrease_speed(ball, ball->speed * p2->damp_force);
        }

        glm_vec3_zero(tmp);
        player_anchor(p2, tmp);
        change_direction(ball, tmp);
    }

    if (SDL_HasIntersection(&br, &twr)) {
        ball->velocity[1] = fabs(ball->velocity[1]);
        decrease_speed_defaut(ball, delta);
    }

    if (SDL_HasIntersection(&br, &bwr)) {
        ball->velocity[1] = -fabs(ball->velocity[1]);
        decrease_speed_defaut(ball, delta);
    }

    if (!SDL_HasIntersection(&br, &par)) {
        if (ball_out_of_bounds_tid == -1) {
            uint8_t out_from_side = ball->position[0] < p1->position[0]
                ? PLAYER1 : PLAYER2;
            ball_out_of_bounds_tid = SDL_AddTimer(
                1000, ball_out_of_bounds, (void*) (uintptr_t) out_from_side
            );
        }
    }

    increate_min_speed(ball, delta);
    decrease_speed_defaut(ball, delta);

    glm_vec3_zero(tmp);
    glm_vec3_normalize_to(ball->velocity, tmp);
    glm_vec3_scale(tmp, ball->speed * delta, tmp);
    glm_vec3_add(ball->position, tmp, ball->position);

#ifdef DEBUG
    printf("Ball speed: %f <= %f <= %f\n",
        ball->min_speed, ball->speed, ball->max_speed
    );
#endif
}

void change_direction(Ball* ball, vec3 anchor)
{
    glm_vec3_sub(ball->position, anchor, ball->velocity);
}

void increate_min_speed(Ball* ball, double delta)
{
    float speedup = BALL_SPEED_STEP * delta;
    ball->min_speed = fmin(
        ball->min_speed + speedup,
        ball->max_speed
    );
}

void decrease_speed_defaut(Ball* ball, double delta)
{
    decrease_speed(ball, BALL_SPEED_STEP * delta);
}

void decrease_speed(Ball* ball, double slowdown)
{
    ball->speed = fmin(
        fmax(ball->speed - slowdown, ball->min_speed),
        ball->max_speed
    );
}

void ball_render(Ball* ball)
{
    object_render(ball);
}
