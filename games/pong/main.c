#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>

#include <cglm/vec3.h>

#include <sdl2/timer.h>
#include <utils/macros.h>

#define PLAYER1 0
#define PLAYER2 1
#define PLAYER_MAX_SPEED 300

typedef enum {
    ACTION_UP, ACTION_DOWN, ACTIONS_SIZE
} Actions;

typedef struct Settings {
    struct {
        const char* title;
        int width;
        int height;
    } window;
    struct {
        SDL_Color clear_color;
        bool vsync;
    } renderer;
    struct {
        double fps;
    } physics;
} Settings;

typedef struct Engine {
    Settings settings;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
} Engine;

typedef struct Player {
    SDL_Color color;
    SDL_Rect shape;
    vec3 position;
    float speed;
    bool actions[ACTIONS_SIZE];
} Player;

typedef struct Game {
    Settings settings;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;

    Player players[2];
} Game;


static Game game;

void initialize_game(void);
void initialize_settings(void);
bool setup_window(void);
bool setup_renderer(void);
void setup_game(void);
void finalize_game(void);
void destroy_renderer(void);
void destroy_window(void);

void process_event(SDL_Event* event);
void physics_process(void);
void process(double delta);
void draw(void);

void renderer_clear(void);
void renderer_draw_rect(SDL_Rect rect, SDL_Color color);
void renderer_present(void);

void player_input(Player* player, SDL_Event* event);
void cpu_input(Player* player);
void player_physics_process(Player* player, double delta);
void player_render(Player* player);

int window_width(void);
int window_height(void);
SDL_Color clear_color(void);
double physics_fps(void);
double physics_delta(void);
Player* player1(void);
Player* player2(void);

bool in_array(int needle, int* array, size_t size);

int main(void)
{
    atexit(finalize_game);

    initialize_game();

    double a_physics_tick = 0.0;
    double last_count = timer_get_ticks_in_seconds();
    double delta = physics_delta();

    while (game.running) {
        double now = timer_get_ticks_in_seconds();
        delta = now - last_count;
        last_count = now;
        a_physics_tick += delta;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game.running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    game.running = false;
                }
            }

            process_event(&event);
        }

        if (a_physics_tick >= physics_delta()) {
            physics_process();
            a_physics_tick -= physics_delta();
        }

        process(delta);

        draw();
    }

    return 0;
}

void initialize_game(void)
{
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);

    initialize_settings();

    game.running = setup_window() && setup_renderer();

    setup_game();
}

void initialize_settings(void)
{
    game.settings = (Settings){
        .window = {
            .title = "PONG",
            .width = 800,
            .height = 600
        },
        .renderer = {
            .clear_color = {
                0, 0, 0, SDL_ALPHA_OPAQUE
            },
            .vsync = true
        },
        .physics = {
            .fps = 60.0
        }
    };
}

bool setup_window(void)
{
    game.window = SDL_CreateWindow(
        game.settings.window.title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        game.settings.window.width, game.settings.window.height,
        SDL_WINDOW_SHOWN
    );
    if (game.window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
            "Couldn't create SDL Window\n\tError: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool setup_renderer(void)
{
    Uint32 flags = SDL_RENDERER_ACCELERATED;
    if (game.settings.renderer.vsync) {
        flags |= SDL_RENDERER_PRESENTVSYNC;
    }

    game.renderer = SDL_CreateRenderer(game.window, -1, flags);
    if (game.renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
            "Couldn't create SDL Renderer\n\tError: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void setup_game(void)
{
    float center_y = window_height()/2.0f;
    game.players[PLAYER1] = (Player){
        .color = {255, 255, 255, SDL_ALPHA_OPAQUE},
        .shape = {0, 0, 20, 80},
        .position = {15, center_y, 0},
        .speed = PLAYER_MAX_SPEED,
        .actions = {0}
    };
    game.players[PLAYER2] = (Player){
        .color = {255, 255, 255, SDL_ALPHA_OPAQUE},
        .shape = {200, 0, 20, 80},
        .position = {window_width() - 15, center_y, 0},
        .speed = PLAYER_MAX_SPEED,
        .actions = {0}
    };
}

void finalize_game(void)
{
    destroy_renderer();
    destroy_window();
}

void destroy_renderer(void)
{
    SDL_DestroyRenderer(game.renderer);
    game.renderer = NULL;
}

void destroy_window(void)
{
    SDL_DestroyWindow(game.window);
    game.window = NULL;
}

void process_event(SDL_Event* event)
{
    player_input(player1(), event);
}

void physics_process(void)
{
    player_physics_process(player1(), physics_delta());
    player_physics_process(player2(), physics_delta());
}

void process(double delta)
{
    cpu_input(player2());
}

void draw(void)
{
    renderer_clear();

    player_render(player1());
    player_render(player2());

    renderer_present();
}

void renderer_clear(void)
{
    SDL_Color color = clear_color();
    SDL_SetRenderDrawColor(game.renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(game.renderer);
}

void renderer_draw_rect(SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(game.renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(game.renderer, &rect);
}

void renderer_present(void)
{
    SDL_RenderPresent(game.renderer);
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

void player_physics_process(Player* player, double delta)
{
    vec3 velocity = {0};
    velocity[1] = player->actions[ACTION_DOWN] - player->actions[ACTION_UP];

    vec3 tmp = {0};
    glm_vec3_normalize_to(velocity, tmp);
    glm_vec3_scale(tmp, player->speed * delta, tmp);

    glm_vec3_add(player->position, tmp, player->position);
}

void player_render(Player* player)
{
    SDL_Rect rect = player->shape;
    rect.x = player->position[0] - rect.w/2.0f;
    rect.y = player->position[1] - rect.h/2.0f;
    SDL_Color color = player->color;
    renderer_draw_rect(rect, color);
}

int window_width(void)
{
    return game.settings.window.width;
}

int window_height(void)
{
    return game.settings.window.height;
}

SDL_Color clear_color(void)
{
    return game.settings.renderer.clear_color;
}

double physics_fps(void)
{
    return game.settings.physics.fps;
}

double physics_delta(void)
{
    return 1.0 / physics_fps();
}

Player* player1(void)
{
    return &game.players[PLAYER1];
}

Player* player2(void)
{
    return &game.players[PLAYER2];
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
