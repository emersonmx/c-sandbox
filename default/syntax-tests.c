#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void ExitFunc(void);

size_t mystrlen(char const string[static 1])
{
    return strlen(string);
}

int myatexit(ExitFunc func)
{
    return atexit(func);
}

void bye(void)
{
    printf("Bye bye\n");
}

int main(int argc, char* argv[argc+1]) {
    myatexit(bye);
    mystrlen("test");
    return EXIT_SUCCESS;
}


