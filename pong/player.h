#ifndef PONG_PLAYER_H
#define PONG_PLAYER_H

#include <cglm/vec3.h>

#include <sdl2/sdl2.h>

#include "render.h"

#define PLAYER1 0
#define PLAYER2 1
#define PLAYER_MAX_SPEED 300
#define PLAYER_DEFAULT_HIT_FORCE 2
#define PLAYER_DEFAULT_DAMP_FORCE 0.2

#ifdef __cplusplus
extern "C" {
#endif

typedef void PlayerInputVelocityFunc(uint8_t player_id, vec3 dest);

typedef struct Player {
    uint8_t id;
    SDL_Color color;
    SDL_Rect rect;
    vec3 position;
    double speed;
    double hit_force;
    double damp_force;
    bool is_strong_hit;

    PlayerInputVelocityFunc* input_velocity_func;
} Player;


SDL_Rect player_rect(Player* player);
void player_anchor(Player* player, vec3 dest);

void player_default_input_velocity_func(uint8_t player_id, vec3 dest);
void player_ia_input_velocity_func(uint8_t player_id, vec3 dest);

void player_fixed_update(Player* player, double delta);
void player_render(Player* player);

#ifdef __cplusplus
}
#endif

#endif /* PONG_PLAYER_H */
