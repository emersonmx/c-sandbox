#ifndef CSB_UTILS_RANDOM_H
#define CSB_UTILS_RANDOM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void randomize(void);
void random_seed(uint_fast32_t seed);

int random_int(int min, int max);
double random_number(double min, double max);

#ifdef __cplusplus
}
#endif

#endif /* CSB_UTILS_RANDOM_H */
