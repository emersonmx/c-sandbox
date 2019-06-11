#ifndef PONG_EVENTS_H
#define PONG_EVENTS_H

#include <stdbool.h>

#include <SDL_stdinc.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    BALL_OUT_OF_BOUNDS_EVENT, PLAY_BALL_EVENT, EVENTS_SIZE
};


bool events_init(void);
void events_quit(void);
Uint32 events_get_id(void);

#ifdef __cplusplus
}
#endif

#endif /* PONG_EVENTS_H */
