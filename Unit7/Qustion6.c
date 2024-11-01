#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    long* nums = calloc(8, sizeof(long));
    
    for (size_t i = 0; i < 8; i++)
    {
        printf("%ld ", *(nums + i));
    }

    printf("\n");
    long** numsptr = (long**)calloc(8, sizeof(long*));

    for (size_t i = 0; i < 8; i++)
    {
        printf("%p ", numsptr[i]);
    }
    printf("\n");
    
    return 0;
}
