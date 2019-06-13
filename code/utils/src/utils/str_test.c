#include <stdio.h>

#include "str.h"

int main()
{
    char* hello = str_format("Hello %s", "world");
    printf("%s\n", hello);

    char* calc = str_format("%d + %d = %d", 2, 2, 4);
    printf("%s\n", calc);

    char* noargs = str_format("No args");
    printf("%s\n", noargs);

    free(noargs);
    free(calc);
    free(hello);
    return 0;
}
