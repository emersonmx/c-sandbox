#include "score.h"

#include <utils/str.h>
#include <utils/macros.h>

#include "pong.h"

static void update_texture(Score* score)
{
    Pong* pong = pong_instance();

    char* text = str_format("%d", score->value);
    SDL_Surface* surface = TTF_RenderUTF8_Blended(
        pong->score_font,
        text,
        score->color
    );
    free(text);
    RETURN_IF_NULL(surface);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(
        engine_renderer(), surface
    );
    SDL_FreeSurface(surface);
    RETURN_IF_NULL(texture);

    score->texture = texture;
    SDL_zero(score->rect);
    SDL_QueryTexture(
        score->texture, NULL, NULL, &score->rect.w, &score->rect.h
    );
}

void score_update_score(Score* score, int value)
{
    score->value = value;
    update_texture(score);
}

void score_reset(Score* score)
{
    glm_vec3_zero(score->position);
    glm_vec3_zero(score->origin);
    score->value = 0;
}

void score_render(Score* score)
{
    SDL_Rect rect = score->rect;
    rect.x = score->position[0] - rect.w/2.0f;
    rect.y = score->position[1] - rect.h/2.0f;
    rect.x = score->position[0] - (rect.w * score->origin[0]);
    rect.y = score->position[1] - (rect.h * score->origin[1]);
    SDL_RenderCopy(engine_renderer(), score->texture, NULL, &rect);
}
