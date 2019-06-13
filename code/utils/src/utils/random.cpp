#include "random.h"

#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

void randomize(void)
{
    random_seed(rd());
}

void random_seed(uint_fast32_t seed)
{
    gen.seed(seed);
}

int random_int(int min, int max)
{
    return std::uniform_int_distribution<>(min, max)(gen);
}

double random_number(double min, double max)
{
    return std::uniform_real_distribution<>(min, max)(gen);
}
