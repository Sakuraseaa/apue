/**
 * @file 1_3_ls.c It can list all files of a directory.
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "apue.h"
#include <dirent.h>

int main(int argc, char const *argv[])
{
    DIR *dp;
    struct dirent *dirp;

    if (argc != 2)
    {
        err_quit("usage: ls directory_name");
    }

    if ((dp = opendir(argv[1])) == NULL)
    {
        err_quit("can't open %s\n", argv[1]);
    }

    for (int i = 1; (dirp = readdir(dp)) != NULL; i++)
    {
        printf("%s ", dirp->d_name);
        if ((i % 4) == 0)
        {
            printf("\n");
        }
    }

    return 0;
}
