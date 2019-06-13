#include "event.h"

#include <sdl2/engine.h>

static uint32_t event_id;

bool event_init(void)
{
    event_id = SDL_RegisterEvents(1);
    if (event_id == (uint32_t)-1) {
        return false;
    }

    return true;
}

void event_quit(void)
{
    event_id = (uint32_t) -1;
}

uint32_t event_get_id(void)
{
    return event_id;
}
