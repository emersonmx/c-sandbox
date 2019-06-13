#include <stdio.h>

#include "random.h"

int main(void)
{
    printf("FIXED SEED\n");
    random_seed(1);
    printf("%d\n", random_int(0, 10));
    printf("%d\n", random_int(0, 10));
    printf("%d\n", random_int(0, 10));
    printf("%d\n", random_int(0, 10));
    printf("%f\n", random_number(0, 10));
    printf("%f\n", random_number(0, 10));
    printf("%f\n", random_number(0, 10));
    printf("%f\n", random_number(0, 10));

    printf("RANDOM SEED\n");
    randomize();
    printf("%d\n", random_int(0, 10));
    printf("%d\n", random_int(0, 10));
    printf("%d\n", random_int(0, 10));
    printf("%d\n", random_int(0, 10));
    printf("%f\n", random_number(0, 10));
    printf("%f\n", random_number(0, 10));
    printf("%f\n", random_number(0, 10));
    printf("%f\n", random_number(0, 10));
}
