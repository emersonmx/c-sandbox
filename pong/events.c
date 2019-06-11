#include "events.h"

#include <sdl2/engine.h>

static Uint32 event_id;

bool events_init(void)
{
    event_id = SDL_RegisterEvents(1);
    if (event_id == (Uint32)-1) {
        return false;
    }

    return true;
}

void events_quit(void)
{
    event_id = (Uint32) -1;
}

Uint32 events_get_id(void)
{
    return event_id;
}
