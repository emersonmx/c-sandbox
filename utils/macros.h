#ifndef UTILS_MACROS_H
#define UTILS_MACROS_H

#include <assert.h>

#define RETURN_VALUE_IF_TRUE(X, R) \
    if (X) { \
        return R; \
    }

#define RETURN_VALUE_IF_NULL(X, R) RETURN_VALUE_IF_TRUE(X == NULL, R)
#define RETURN_IF_NULL(X) RETURN_VALUE_IF_NULL(X,)
#define ASSERT_VALID_OBJECT(X) assert(X != NULL)

#endif /* UTILS_MACROS_H */
