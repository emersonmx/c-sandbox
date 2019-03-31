#ifndef CSB_SDL2_MACROS_H
#define CSB_SDL2_MACROS_H

#include <utils/macros.h>

#define RETURN_WITH_LOG_IF_TRUE(X, M) \
    if (X) {                          \
        M;                            \
        return;                       \
    }
#define RETURN_WITH_LOG_IF_FALSE(X, M) \
    RETURN_WITH_LOG_IF_TRUE(!X, M)
#define RETURN_WITH_LOG_IF_NULL(X, M) \
    RETURN_WITH_LOG_IF_TRUE(IS_NULL(X), M)

#endif /* CSB_SDL2_MACROS_H */
