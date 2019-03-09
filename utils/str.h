#ifndef CSB_UTILS_STR_H
#define CSB_UTILS_STR_H

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

char* str_format(const char* format, ...)
{
    va_list args1;
    va_start(args1, format);
    va_list args2;
    va_copy(args2, args1);
    int size = vsnprintf(NULL, 0, format, args1);
    va_end(args1);
    int total_size = size + 1;
    char* buffer = calloc(total_size, sizeof(char));
    vsnprintf(buffer, total_size, format, args2);
    va_end(args2);

    return buffer;
}

#ifdef __cplusplus
}
#endif

#endif /* CSB_UTILS_STR_H */
