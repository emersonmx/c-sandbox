#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>

#include <cglm/vec3.h>

#include <utils/macros.h>

#define PLAYER1 0
#define PLAYER2 1

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
} Player;

typedef struct Game {
    Settings settings;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;

    Player players[2];
} Game;


Game game;

void initialize_settings(void);
void setup_game(void);

void initialize_game(void);
void finalize_game(void);

void renderer_clear(void);
void renderer_draw_rect(SDL_Rect rect, SDL_Color color);
void renderer_present(void);

Settings get_game_settings(void);
void render_player(Player* player);

int main(void)
{
    initialize_settings();

    initialize_game();

    setup_game();

    while (game.running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game.running = false;
            }
        }

        renderer_clear();
        render_player(&game.players[PLAYER1]);
        render_player(&game.players[PLAYER2]);
        renderer_present();
    }

    return 0;
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
        }
    };
}

void setup_game(void)
{
    float center_y = game.settings.window.height/2;
    game.players[PLAYER1] = (Player){
        .color = {255, 255, 255, SDL_ALPHA_OPAQUE},
        .shape = {0, 0, 20, 80},
        .position = {15, center_y, 0}
    };
    game.players[PLAYER2] = (Player){
        .color = {255, 255, 255, SDL_ALPHA_OPAQUE},
        .shape = {200, 0, 20, 80},
        .position = {game.settings.window.width - 15, center_y, 0}
    };
}

SDL_Window* create_sdl_window(void)
{
    SDL_Window* window = SDL_CreateWindow(
        game.settings.window.title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        game.settings.window.width, game.settings.window.height,
        SDL_WINDOW_SHOWN
    );
    RETURN_NULL_IF_NULL(window);

    return window;
}

void destroy_sdl_window(SDL_Window* window)
{
    SDL_DestroyWindow(window);
}

SDL_Renderer* create_sdl_renderer(void)
{
    Uint32 flags = SDL_RENDERER_ACCELERATED;
    if (game.settings.renderer.vsync) {
        flags |= SDL_RENDERER_PRESENTVSYNC;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(game.window, -1, flags);
    RETURN_NULL_IF_NULL(renderer);

    return renderer;
}

void destroy_sdl_renderer(SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
}

void initialize_game(void)
{
    game.window = create_sdl_window();
    if (game.window == NULL) {
        SDL_Log("Couldn't create SDL Window\n\tError: %s\n", SDL_GetError());
        game.running = false;
        return;
    }

    game.renderer = create_sdl_renderer();
    if (game.renderer == NULL) {
        SDL_Log("Couldn't create SDL Renderer\n\tError: %s\n", SDL_GetError());
        game.running = false;
        return;
    }

    game.running = true;
}

void finalize_game(void)
{
    destroy_sdl_renderer(game.renderer);
    destroy_sdl_window(game.window);
}

void renderer_clear(void)
{
    SDL_Color color = game.settings.renderer.clear_color;
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

void render_player(Player* player)
{
    SDL_Rect rect = player->shape;
    rect.x = player->position[0] - rect.w/2.0f;
    rect.y = player->position[1] - rect.h/2.0f;
    SDL_Color color = player->color;
    renderer_draw_rect(rect, color);
}
