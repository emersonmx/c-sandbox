#include "event.h"

#include <sdl2/engine.h>

static Uint32 event_id;

bool event_init(void)
{
    event_id = SDL_RegisterEvents(1);
    if (event_id == (Uint32)-1) {
        return false;
    }

    return true;
}

void event_quit(void)
{
    event_id = (Uint32) -1;
}

Uint32 event_get_id(void)
{
    return event_id;
}
