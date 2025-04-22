/**
 * @file 1_q1.c .. and .
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

/* Advanced Programming in the UNIX Enviroment*/
#include "apue.h"

int main(int argc, char const *argv[])
{
    struct stat s1;
    struct stat s2;

    stat(".", &s1);
    stat("..", &s2);
    printf("[.]:dev:%ld inode:%ld nlinke:%ld size:%ld\n", s1.st_dev, s1.st_ino, s1.st_nlink, s1.st_size);
    printf("[..]:dev:%ld inode:%ld nlinke:%ld size:%ld\n", s2.st_dev, s2.st_ino, s2.st_nlink, s2.st_size);
    return 0;
}

