#include "pong.h"

static Pong game = {0};

Pong* pong_instance(void)
{
    return &game;
}
