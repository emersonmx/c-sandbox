#include "player.h"

#include "pong.h"
#include "utils.h"
#include "object.h"

SDL_Rect player_rect(Player* player)
{
    return object_rect(player);
}

void player_default_input_velocity_func(int index, vec3 dest)
{
    Pong* game = pong_instance();

    int action_up = index == PLAYER1 ? PLAYER1_ACTION_UP : PLAYER2_ACTION_UP;
    int action_down = index == PLAYER1
        ? PLAYER1_ACTION_DOWN : PLAYER2_ACTION_DOWN;

    dest[1] = game->actions[action_down] - game->actions[action_up];
}

void player_ia_input_velocity_func(int index, vec3 dest)
{
}

void player_fixed_update(Player* player, double delta)
{
    Pong* game = pong_instance();

    vec3 velocity;
    glm_vec3_zero(velocity);

    player->input_velocity_func(player->index, velocity);

    vec3 tmp = {0};
    glm_vec3_normalize_to(velocity, tmp);
    glm_vec3_scale(tmp, player->speed * delta, tmp);

    glm_vec3_add(player->position, tmp, player->position);

    SDL_Rect pr = player_rect(player);
    SDL_Rect twr = wall_rect(&game->walls[TOP_WALL]);
    SDL_Rect bwr = wall_rect(&game->walls[BOTTOM_WALL]);

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
