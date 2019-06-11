#ifndef PONG_EVENT_H
#define PONG_EVENT_H

#include <stdbool.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    BALL_OUT_OF_BOUNDS_EVENT, PLAY_BALL_EVENT, EVENTS_SIZE
};


bool event_init(void);
void event_quit(void);
uint32_t event_get_id(void);

#ifdef __cplusplus
}
#endif

#endif /* PONG_EVENT_H */
