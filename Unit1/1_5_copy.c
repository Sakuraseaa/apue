/**
 * @file 1_5_copy.c The rountine copies standard input stream to strandard output strem
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "apue.h"

int main(int argc, char const *argv[])
{
    int c;
    while ((c = getc(stdin)) != EOF)
    {
        if (putc(c, stdout) == EOF)
        {
            err_sys("output error");
        }
        /* code */
    }

    if (ferror(stdin))
    {
        err_sys("input error");
    }
    
    return 0;
}
