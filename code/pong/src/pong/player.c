#include "player.h"

#include <stdint.h>

#include "render.h"
#include "app.h"
#include "utils.h"
#include "object.h"
#include "action.h"

#define DEFAULT_ANGLE 30

static double calc_height(double base, double angle);

SDL_Rect player_rect(Player* player)
{
    return object_rect(player);
}

void player_anchor(Player* player, vec3 dest)
{
    int8_t direction = player->id == PLAYER1 ? -1 : 1;
    double offset = calc_height(
        player->rect.h,
        DEFAULT_ANGLE
    );
    glm_vec3_copy(player->position, dest);
    dest[0] += (player->rect.w/2.0) + offset*direction;
}

double calc_height(double base, double angle)
{
    return (base/2.0) * tan(glm_rad(angle));
}

void player_default_input_velocity_func(uint8_t player_id, vec3 dest)
{
    uint8_t up_action = player_id == PLAYER1
        ? PLAYER1_UP_ACTION : PLAYER2_UP_ACTION;
    uint8_t down_action = player_id == PLAYER1
        ? PLAYER1_DOWN_ACTION : PLAYER2_DOWN_ACTION;

    dest[1] = action_is_pressed(down_action) - action_is_pressed(up_action);
}

void player_ia_input_velocity_func(uint8_t player_id, vec3 dest)
{
    App* app = app_instance();
    int32_t window_width = app->settings.window.width;
    int32_t center_y = app->settings.window.height / 2.0f;

    Ball* ball = &app->game.ball;
    Player* player = player_id == PLAYER1
        ? &app->game.player1 : &app->game.player2;

    int32_t area = window_width * 0.8f;
    int32_t player_x = player->position[0];
    int32_t player_y = player->position[1];
    int32_t ball_x = ball->position[0];
    int32_t ball_y = ball->position[1];
    int32_t diff_x = abs(ball_x - player_x);
    int32_t inside_of_bounds = 0 < ball_x && ball_x < window_width;
    int32_t offset = 10;

    if (diff_x < area && inside_of_bounds) {
        if (player_y - offset > ball_y) {
            dest[1] = -1;
        } else if (player_y + offset < ball_y) {
            dest[1] = 1;
        }
    } else {
        if (player_y - offset > center_y) {
            dest[1] = -1;
        } else if (player_y + offset < center_y) {
            dest[1] = 1;
        }
    }
}

void player_fixed_update(Player* player, double delta)
{
    App* app = app_instance();

    vec3 velocity;
    glm_vec3_zero(velocity);

    player->input_velocity_func(player->id, velocity);

    player->is_strong_hit = fabsf(velocity[1]) > 0;

    vec3 tmp = {0};
    glm_vec3_normalize_to(velocity, tmp);
    glm_vec3_scale(tmp, player->speed * delta, tmp);

    glm_vec3_add(player->position, tmp, player->position);

    SDL_Rect pr = player_rect(player);
    SDL_Rect twr = wall_rect(&app->game.top_wall);
    SDL_Rect bwr = wall_rect(&app->game.bottom_wall);

    if (SDL_HasIntersection(&pr, &twr)) {
        player->position[1] = twr.y+twr.h + player->rect.h/2.0f;
    }

    if (SDL_HasIntersection(&pr, &bwr)) {
        player->position[1] = bwr.y - player->rect.h/2.0f;
    }
}

void player_update(Player* player, double delta)
{
}

void player_render(Player* player)
{
    object_render(player);
}
