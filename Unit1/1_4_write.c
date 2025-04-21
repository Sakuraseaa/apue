/**
 * @file 1_4_write.c Read form standard output stream and write to standard input.
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "apue.h"
#define BUFFSIZE 4096

int main(int argc, char const *argv[])
{
    int n;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buf, n) != n)
        {
            err_sys("write error");
        }
    }

    if (n < 0)
    {
        err_sys("read error");
    }
    
    return 0;
}
