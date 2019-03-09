#include "ball.h"

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

    glm_vec3_copy(GLM_XUP, ball->velocity);
    glm_vec3_rotate(ball->velocity, GLM_PI_4, GLM_ZUP);

    ball->velocity[0] *= (rand() % 2 == 0) ? -1 : 1;

    printf("%f, %f, %f\n",
        ball->velocity[0],
        ball->velocity[1],
        ball->velocity[2]
    );

    // position = game_area.size / 2
    // speed = min_speed
    // velocity = Vector2()

    // var timer = $timer
    // timer.start()
    // yield(timer, 'timeout')

    // randomize()
    // velocity = Vector2(1, 0)
    // velocity = velocity.rotated(rand_range(PI/4, -PI/4))
    // velocity.x *= -1 if randi() % 2 == 0 else 1
}

void ball_input(Ball* ball, SDL_Event* event)
{
}

void ball_fixed_update(Ball* ball, double delta)
{
}

void ball_update(Ball* ball, double delta)
{
}

void ball_render(Ball* ball)
{
    object_render(ball);
}
