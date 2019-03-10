#ifndef CSB_GAMES_PONG_PLAYER_H
#define CSB_GAMES_PONG_PLAYER_H

#include <cglm/vec3.h>

#include <sdl2/sdl2.h>

#include "render.h"

#define PLAYER1 0
#define PLAYER2 1
#define PLAYER_MAX_SPEED 300

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*PlayerInputVelocityFunc)(int index, vec3 dest);

typedef struct Player {
    int index;
    SDL_Color color;
    SDL_Rect rect;
    vec3 position;
    float speed;

    PlayerInputVelocityFunc input_velocity_func;
} Player;


SDL_Rect player_rect(Player* player);
void player_default_input_velocity_func(int index, vec3 dest);
void player_ia_input_velocity_func(int index, vec3 dest);

void player_fixed_update(Player* player, double delta);
void player_update(Player* player, double delta);
void player_render(Player* player);

#ifdef __cplusplus
}
#endif

#endif /* CSB_GAMES_PONG_PLAYER_H */
