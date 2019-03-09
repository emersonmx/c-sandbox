#include "player.h"

#include "pong.h"
#include "utils.h"

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
    vec3 velocity;
    glm_vec3_zero(velocity);

    player->input_velocity_func(player->index, velocity);

    vec3 tmp = {0};
    glm_vec3_normalize_to(velocity, tmp);
    glm_vec3_scale(tmp, player->speed * delta, tmp);

    glm_vec3_add(player->position, tmp, player->position);
}

void player_update(Player* player, double delta)
{
}

void player_render(Player* player)
{
    object_render(player);
}