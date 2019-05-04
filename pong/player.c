#include "player.h"

#include "pong.h"
#include "utils.h"
#include "object.h"

#define DEFAULT_ANGLE 30

static double calc_height(double base, double angle);

SDL_Rect player_rect(Player* player)
{
    return object_rect(player);
}

void player_anchor(Player* player, vec3 dest)
{
    uint8_t direction = player->id == PLAYER1 ? -1 : 1;
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
    uint8_t action_up = player_id == PLAYER1
        ? PLAYER1_ACTION_UP : PLAYER2_ACTION_UP;
    uint8_t action_down = player_id == PLAYER1
        ? PLAYER1_ACTION_DOWN : PLAYER2_ACTION_DOWN;

    dest[1] = action_is_pressed(action_down) - action_is_pressed(action_up);
}

void player_ia_input_velocity_func(uint8_t player_id, vec3 dest)
{
    Pong* pong = pong_instance();
    int window_width = pong->settings.window.width;
    int center_y = pong->settings.window.height / 2.0f;

    Ball* ball = &pong->ball;
    Player* player = player_id == PLAYER1 ? &pong->player1 : &pong->player2;

    int area = window_width * 0.8f;
    int player_x = player->position[0];
    int player_y = player->position[1];
    int ball_x = ball->position[0];
    int ball_y = ball->position[1];
    int diff_x = abs(ball_x - player_x);
    int inside_of_bounds = 0 < ball_x && ball_x < window_width;
    int offset = 10;

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
    Pong* game = pong_instance();

    vec3 velocity;
    glm_vec3_zero(velocity);

    player->input_velocity_func(player->id, velocity);

    player->is_strong_hit = fabsf(velocity[1]) > 0;

    vec3 tmp = {0};
    glm_vec3_normalize_to(velocity, tmp);
    glm_vec3_scale(tmp, player->speed * delta, tmp);

    glm_vec3_add(player->position, tmp, player->position);

    SDL_Rect pr = player_rect(player);
    SDL_Rect twr = wall_rect(&game->top_wall);
    SDL_Rect bwr = wall_rect(&game->bottom_wall);

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
