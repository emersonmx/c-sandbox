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


static Game game;

void initialize_game(void);
void initialize_settings(void);
bool setup_window(void);
bool setup_renderer(void);
void setup_game(void);
void finalize_game(void);
void destroy_renderer(void);
void destroy_window(void);

void renderer_clear(void);
void renderer_draw_rect(SDL_Rect rect, SDL_Color color);
void renderer_present(void);

void player_render(Player* player);

int window_width(void);
int window_height(void);
SDL_Color clear_color(void);

int main(void)
{
    atexit(finalize_game);

    initialize_game();

    while (game.running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game.running = false;
            }
        }

        renderer_clear();
        player_render(&game.players[PLAYER1]);
        player_render(&game.players[PLAYER2]);
        renderer_present();
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
        .position = {15, center_y, 0}
    };
    game.players[PLAYER2] = (Player){
        .color = {255, 255, 255, SDL_ALPHA_OPAQUE},
        .shape = {200, 0, 20, 80},
        .position = {window_width() - 15, center_y, 0}
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
