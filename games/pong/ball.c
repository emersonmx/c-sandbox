#include "ball.h"

#include <utils/random.h>

#include "pong.h"
#include "object.h"

static void change_direction(Ball* ball, vec3 anchor);
static void increate_min_speed(Ball* ball, double delta);
static void decrease_speed_defaut(Ball* ball, double delta);
static void decrease_speed(Ball* ball, double slowdown);

SDL_Rect ball_rect(Ball* ball)
{
    return object_rect(ball);
}

void ball_reset(Ball* ball)
{
    Pong* game = pong_instance();

    glm_vec3_copy((vec3){
        game->settings.window.width / 2.0f,
        game->settings.window.height / 2.0f,
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

void ball_fixed_update(Ball* ball, double delta)
{
    vec3 tmp;
    Pong* game = pong_instance();
    Player* p1 = &game->players[PLAYER1];
    Player* p2 = &game->players[PLAYER2];
    SDL_Rect br = ball_rect(ball);
    SDL_Rect p1r = player_rect(p1);
    SDL_Rect p2r = player_rect(p2);
    SDL_Rect twr = wall_rect(&game->walls[TOP_WALL]);
    SDL_Rect bwr = wall_rect(&game->walls[BOTTOM_WALL]);

    if (SDL_HasIntersection(&br, &p1r)) {
        bool is_moving = game->actions[PLAYER1_ACTION_UP]
            || game->actions[PLAYER1_ACTION_DOWN];
        if (is_moving) {
            ball->speed = fmax(p1->speed*p1->hit_force, ball->speed);
        } else {
            decrease_speed(ball, ball->speed * p2->damp_force);
        }

        glm_vec3_zero(tmp);
        player_anchor(p1, tmp);
        change_direction(ball, tmp);
    }

    if (SDL_HasIntersection(&br, &p2r)) {
        bool is_moving = game->actions[PLAYER2_ACTION_UP]
            || game->actions[PLAYER2_ACTION_DOWN];
        if (is_moving) {
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

    increate_min_speed(ball, delta);
    decrease_speed_defaut(ball, delta);

    glm_vec3_zero(tmp);
    glm_vec3_normalize_to(ball->velocity, tmp);
    glm_vec3_scale(tmp, ball->speed * delta, tmp);
    glm_vec3_add(ball->position, tmp, ball->position);
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
