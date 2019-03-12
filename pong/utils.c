#include "utils.h"

bool in_array(int needle, int* array, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        if (needle == array[i]) {
            return true;
        }
    }
    return false;
}
