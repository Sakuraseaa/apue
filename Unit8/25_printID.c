#include "apue.h"

int main(int argc, char const *argv[])
{
    printf("real uid = %d, effective uid = %d\n", getuid(), getuid());
    return 0;
}
