#include "text.h"

#include <SDL_ttf.h>

#include <utils/macros.h>

SDL_Texture* create_text(Text* text);

Text* text_new(void)
{
    Text* text = malloc(sizeof(Text));
    RETURN_NULL_IF_NULL(text);

    *text = (const Text){0};

    return text;
}

void text_delete(Text* text)
{
    RETURN_IF_NULL(text);
    text_clear(text);
    free(text);
}

void text_update_texture(Text* text)
{
    ASSERT_VALID_OBJECT(text);

    text->texture = create_text(text);
    SDL_QueryTexture(
        text->texture, NULL, NULL, &text->offset.w, &text->offset.h
    );
}

void text_clear(Text* text)
{
    ASSERT_VALID_OBJECT(text);

    if (text->value != NULL) {
        free(text->value);
    }

    if (text->texture != NULL) {
        SDL_DestroyTexture(text->texture);
    }
}

SDL_Texture* create_text(Text* text)
{
    SDL_Surface* surface = TTF_RenderUTF8_Blended(
        text->font,
        text->value,
        text->color
    );
    RETURN_NULL_IF_NULL(surface);

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(text->renderer, surface);
    SDL_FreeSurface(surface);
    RETURN_NULL_IF_NULL(texture);

    return texture;
}
