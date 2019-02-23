#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <utils/str.h>

typedef struct Engine {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
} Engine;

static Engine* engine = NULL;

typedef struct Text {
    SDL_Texture* texture;
    char* value;
    SDL_Rect offset;
} Text;

Text* text_new(void)
{
    Text* text = malloc(sizeof(Text));
    if (text == NULL) {
        return NULL;
    }

    *text = (const Text){0};

    return text;
}

void text_clear(Text* text)
{
    if (text->value != NULL) {
        free(text->value);
    }

    if (text->texture != NULL) {
        SDL_DestroyTexture(text->texture);
    }
}

void text_free(Text* text)
{
    if (text == NULL) {
        return;
    }

    text_clear(text);
    free(text);
}

SDL_Texture* text__create_text(const char* text)
{
    SDL_Surface* surface = TTF_RenderUTF8_Blended(
        engine->font,
        text,
        (SDL_Color){0x7b, 0, 0x7b, SDL_ALPHA_OPAQUE}
    );
    if (surface == NULL) {
        return NULL;
    }

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(engine->renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {
        return NULL;
    }

    return texture;
}

void text_set_value(Text* text, char* value)
{
    text_clear(text);
    text->value = value;
    text->texture = text__create_text(value);
    SDL_QueryTexture(
        text->texture, NULL, NULL, &text->offset.w, &text->offset.h
    );
}

void init(void)
{
    engine = malloc(sizeof(Engine));
    if (engine == NULL) {
        SDL_Log("Couldn't create app engine.");
        return;
    }

    *engine = (const Engine){0};

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Couldn't start SDL.\n\tError: %s", SDL_GetError());
        return;
    }

    engine->window = SDL_CreateWindow(
        "Resize Test",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
    );
    if (engine->window == NULL) {
        SDL_Log("Couldn't create window.\n\tError: %s", SDL_GetError());
        return;
    }

    engine->renderer = SDL_CreateRenderer(engine->window, -1, SDL_RENDERER_ACCELERATED);
    if (engine->renderer == NULL) {
        SDL_Log("Couldn't create renderer.\n\tError: %s", SDL_GetError());
        return;
    }

    if (TTF_Init() < 0) {
        SDL_Log("Couldn't initialize SDL TTF.\n\tError: %s", TTF_GetError());
        return;
    }

    engine->font = TTF_OpenFont("./assets/fonts/Quicksand-Bold.ttf", 40);
    if (engine->font == NULL) {
        SDL_Log("Couldn't load font.\n\tError: %s", TTF_GetError());
        return;
    }
}

void quit(void)
{
    if (engine != NULL) {
        TTF_CloseFont(engine->font);
        SDL_DestroyRenderer(engine->renderer);
        SDL_DestroyWindow(engine->window);
    }

    TTF_Quit();
    SDL_Quit();

    free(engine);
}

int main(void)
{
    init();

    SDL_Rect window_rect = {0};
    SDL_GetWindowSize(engine->window, &window_rect.w, &window_rect.h);

    SDL_Rect fill_rect = {10, 10, 780, 580};

    Text* text = text_new();
    text_set_value(text, str_format("%dx%d", window_rect.w, window_rect.h));
    text->offset.x = window_rect.w/2 - text->offset.w/2;
    text->offset.y = window_rect.h/2 - text->offset.h/2;

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    window_rect.w = event.window.data1;
                    window_rect.h = event.window.data2;

                    fill_rect.w = window_rect.w - 20;
                    fill_rect.h = window_rect.h - 20;

                    text_set_value(text, str_format("%dx%d", window_rect.w, window_rect.h));
                    text->offset.x = window_rect.w/2 - text->offset.w/2;
                    text->offset.y = window_rect.h/2 - text->offset.h/2;
                }
            }
        }

        SDL_SetRenderDrawColor(engine->renderer, 0x1a, 0, 0x1a, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(engine->renderer);

        SDL_SetRenderDrawColor(engine->renderer, 0x30, 0, 0x30, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(engine->renderer, &fill_rect);

        SDL_RenderCopy(
            engine->renderer,
            text->texture,
            NULL,
            &text->offset
        );

        SDL_RenderPresent(engine->renderer);
    }

    text_free(text);

    quit();

    return 0;
}
