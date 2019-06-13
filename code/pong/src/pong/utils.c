#include "utils.h"

bool in_array(int32_t needle, int32_t* array, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        if (needle == array[i]) {
            return true;
        }
    }
    return false;
}
