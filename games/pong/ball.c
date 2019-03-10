#include "ball.h"

#include <utils/random.h>

#include "pong.h"

void ball_reset(Ball* ball)
{
    Pong* game = pong_instance();

    glm_vec3_copy((vec3){
        game->settings.window.width / 2.0f,
        game->settings.window.height / 2.0f,
        0
    }, ball->position);
    ball->speed = BALL_MIN_SPEED;
    glm_vec3_copy(GLM_VEC3_ZERO, ball->velocity);

    // wait

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
    glm_vec3_normalize_to(ball->velocity, tmp);
    glm_vec3_scale(tmp, ball->speed * delta, tmp);
    glm_vec3_add(ball->position, tmp, ball->position);
}

void ball_render(Ball* ball)
{
    object_render(ball);
}
