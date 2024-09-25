#include "apue.h"

extern char **environ;
int main(void) {

    char* s = environ[0];
    while(environ) {
        s = *environ;
        printf("%s\n", s);
        environ++;
    }

    return 0;
}