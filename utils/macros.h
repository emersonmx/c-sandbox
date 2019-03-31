#ifndef CSB_UTILS_MACROS_H
#define CSB_UTILS_MACROS_H

#include <assert.h>

#define RETURN_VALUE_IF_TRUE(X, R) \
    if (X) {                       \
        return R;                  \
    }

#define RETURN_VALUE_IF_NULL(X, R) RETURN_VALUE_IF_TRUE(!(X), R)
#define RETURN_NULL_IF_NULL(X) RETURN_VALUE_IF_NULL(X, NULL)
#define RETURN_IF_NULL(X) RETURN_VALUE_IF_NULL(X,)
#define ASSERT_VALID_OBJECT(X) assert(X != NULL)

#endif /* CSB_UTILS_MACROS_H */
