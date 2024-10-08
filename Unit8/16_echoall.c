#include "apue.h"

int main(int argc, char const *argv[])
{
    int i;
    extern char** environ;

    for (size_t i = 0; i < argc; i++)
    {   /* echo all command-line args */
        printf("argv[%ld]: %s\n", i, argv[i]);
    }
    
    for (char** ptr = environ; *ptr != 0; ptr++)
    {
        printf("%s\n", *ptr);
    }
    
    return 0;
}
