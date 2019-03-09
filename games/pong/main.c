#include <stdio.h>
#include <stdbool.h>

#include <cglm/vec3.h>

#include <sdl2/engine.h>
#include <utils/macros.h>

#define PLAYER1 0
#define PLAYER2 1
#define PLAYER_MAX_SPEED 300
#define BALL_MAX_SPEED 300

#define object_render(O) { \
        SDL_Rect rect = (O)->rect; \
        rect.x = (O)->position[0] - rect.w/2.0f; \
        rect.y = (O)->position[1] - rect.h/2.0f; \
        SDL_Color color = (O)->color; \
        renderer_draw_rect(rect, color); \
    }

typedef enum {
    ACTION_UP, ACTION_DOWN, ACTIONS_SIZE
} Actions;

typedef struct Player {
    SDL_Color color;
    SDL_Rect rect;
    vec3 position;
    float speed;
    bool actions[ACTIONS_SIZE];
} Player;

typedef struct Ball {
    SDL_Color color;
    SDL_Rect rect;
    vec3 position;
    float speed;
} Ball;

typedef struct Game {
    EngineSettings settings;

    Player players[2];
    Ball ball;
} Game;


static Game game = {0};

static void initialize(void);
static void process_events(SDL_Event* event);
static void fixed_update(double delta);
static void update(double delta);
static void render(void);

static void renderer_draw_rect(SDL_Rect rect, SDL_Color color);

static void player_input(Player* player, SDL_Event* event);
static void cpu_input(Player* player);
static void player_fixed_update(Player* player, double delta);
static void player_update(Player* player, double delta);

static int window_width(void);
static int window_height(void);
static Player* player1(void);
static Player* player2(void);
static Ball* ball(void);

static bool in_array(int needle, int* array, size_t size);

int main(void)
{
    game.settings = engine_default_settings();
    game.settings.window.title = "Pong";

    engine_set_init_func(initialize);
    engine_set_process_events_func(process_events);
    engine_set_fixed_update_func(fixed_update);
    engine_set_update_func(update);
    engine_set_render_func(render);

    return engine_main_loop(game.settings);
}

void initialize(void)
{
    SDL_Color white = {255, 255, 255, SDL_ALPHA_OPAQUE};
    float center_x = window_width() / 2.0f;
    float center_y = window_height() / 2.0f;
    int horizontal_margin = 15;
    game.players[PLAYER1] = (Player){
        .color = white,
        .rect = {0, 0, 20, 80},
        .position = {horizontal_margin, center_y, 0},
        .speed = PLAYER_MAX_SPEED,
        .actions = {0}
    };
    game.players[PLAYER2] = (Player){
        .color = white,
        .rect = {200, 0, 20, 80},
        .position = {window_width() - horizontal_margin, center_y, 0},
        .speed = PLAYER_MAX_SPEED,
        .actions = {0}
    };

    game.ball = (Ball){
        .color = white,
        .rect = {center_x, center_y, 10, 10},
        .position = {center_x, center_y, 0},
        .speed = BALL_MAX_SPEED
    };
}

void process_events(SDL_Event* event)
{
    if (event->type == SDL_QUIT) {
        engine_quit_loop();
    }

    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_ESCAPE) {
            engine_quit_loop();
        }
    }

    player_input(player1(), event);
}

void fixed_update(double delta)
{
    player_fixed_update(player1(), delta);

    cpu_input(player2());
    player_fixed_update(player2(), delta);
}

void update(double delta)
{
    player_update(player1(), delta);
}

void player_update(Player* player, double delta)
{
}

void render(void)
{
    object_render(player1());
    object_render(player2());
    object_render(ball());
}

void renderer_draw_rect(SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(engine_renderer(),
        color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(engine_renderer(), &rect);
}

void player_input(Player* player, SDL_Event* event)
{
    int up_keys[2] = {SDLK_UP, SDLK_w};
    int up_keys_size = sizeof(up_keys)/sizeof(int);
    int down_keys[2] = {SDLK_DOWN, SDLK_s};
    int down_keys_size = sizeof(down_keys)/sizeof(int);

    if (event->type == SDL_KEYDOWN) {
        if (in_array(event->key.keysym.sym, up_keys, up_keys_size)) {
            player->actions[ACTION_UP] = true;
        }
        if (in_array(event->key.keysym.sym, down_keys, down_keys_size)) {
            player->actions[ACTION_DOWN] = true;
        }
    }

    if (event->type == SDL_KEYUP) {
        if (in_array(event->key.keysym.sym, up_keys, up_keys_size)) {
            player->actions[ACTION_UP] = false;
        }
        if (in_array(event->key.keysym.sym, down_keys, down_keys_size)) {
            player->actions[ACTION_DOWN] = false;
        }
    }
}

void cpu_input(Player* player)
{
}

void player_fixed_update(Player* player, double delta)
{
    vec3 velocity = {0};
    velocity[1] = player->actions[ACTION_DOWN] - player->actions[ACTION_UP];

    vec3 tmp = {0};
    glm_vec3_normalize_to(velocity, tmp);
    glm_vec3_scale(tmp, player->speed * delta, tmp);

    glm_vec3_add(player->position, tmp, player->position);
}

int window_width(void)
{
    return game.settings.window.width;
}

int window_height(void)
{
    return game.settings.window.height;
}

Player* player1(void)
{
    return &game.players[PLAYER1];
}

Player* player2(void)
{
    return &game.players[PLAYER2];
}

Ball* ball(void)
{
    return &game.ball;
}

bool in_array(int needle, int* array, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        if (needle == array[i]) {
            return true;
        }
    }
    return false;
}
